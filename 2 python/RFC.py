import numpy as np
import pandas as pd
import matplotlib.pyplot as plt
import seaborn as sns
from scipy import stats
from scipy.signal import find_peaks
import warnings
warnings.filterwarnings('ignore')
import sklearn
from sklearn.preprocessing import StandardScaler, LabelEncoder
from sklearn.ensemble import RandomForestClassifier
from sklearn.model_selection import train_test_split
from sklearn.metrics import accuracy_score, f1_score,classification_report, confusion_matrix
import emlearn

###########################################################################################
audio_df = pd.read_csv('./samlet2.csv', on_bad_lines='skip')
df = audio_df[audio_df['timestamp'] != 0].copy()

df['sample_float'] = (df['samplevalue'].astype(np.int16) - 128).astype(np.float32) / 128.0

files = df['file'].unique()
file_action_map = df.groupby('file')['action'].first()
actions = file_action_map.loc[files].values

train_files, test_files = train_test_split(
    files,
    test_size=0.2,
    stratify=actions,
    random_state=42
)

df_test = df[df['file'].isin(test_files)]
df_train = df[df['file'].isin(train_files)]

###########################################################################################
def extract_features(x):
    features = {}
    
    # Basis statistik
    features['x_mean'] = x.mean()
    features['x_std'] = x.std()
    features['x_aad'] = np.mean(np.absolute(x - np.mean(x)))
    features['x_max'] = x.max()
    features['x_min'] = x.min()
    features['x_maxmin_diff'] = x.max() - x.min()
    features['x_median'] = np.median(x)
    features['x_mad'] = np.median(np.absolute(x - np.median(x)))
    features['x_IQR'] = np.percentile(x, 75) - np.percentile(x, 25)
    
    # Tællinger
    features['x_neg_count'] = np.sum(x < 0)
    features['x_pos_count'] = np.sum(x > 0)
    features['x_above_mean'] = np.sum(x > x.mean())
    features['x_peak_count'] = len(find_peaks(x)[0])
    
    # Højere ordens statistik
    features['x_skewness'] = stats.skew(x)
    features['x_kurtosis'] = stats.kurtosis(x)
    features['x_energy'] = np.sum(x**2) / 100
    
    # Positionsbaserede features
    features['x_argmax'] = np.argmax(x)
    features['x_argmin'] = np.argmin(x)
    features['x_arg_diff'] = abs(features['x_argmax'] - features['x_argmin'])
    
    return features

###########################################################################################
TARGET_LEN = 15800
DOWNSAMPLE_FACTOR = 2

def build_feature_dataset(df_subset, label_encoder):
    feature_list = []
    y_list = []

    for file_id, g in df_subset.groupby('file', sort=False):
        x = g['sample_float'].values
        x = x[:TARGET_LEN]
        x = x[::DOWNSAMPLE_FACTOR]  # Downsample til 7900 samples
        
        # Udtræk features
        features = extract_features(x)
        feature_list.append(features)
        
        y = g['action'].iloc[0]
        y_list.append(y)
    
    # Konverter til DataFrame og derefter numpy array
    X_df = pd.DataFrame(feature_list)
    X = X_df.values

    y_enc = label_encoder.transform(y_list)
    
    return X, y_enc, X_df.columns.tolist()

# Byg feature-baserede datasæt
le = LabelEncoder().fit(df_train['action'])
X_train, y_train, feature_names = build_feature_dataset(df_train, le)
X_test, y_test, _ = build_feature_dataset(df_test, le)

# Label mapping
label_mapping = {i: cls for i, cls in enumerate(le.classes_)}
print(f"Label mapping: {label_mapping}\n")
print(f"Antal features: {len(feature_names)}")

###########################################################################################
# Normaliser features
scaler = StandardScaler()
X_train_scaled = scaler.fit_transform(X_train)
X_test_scaled = scaler.transform(X_test)

# Konverter til DataFrames
X_train_scaled = pd.DataFrame(X_train_scaled, columns=feature_names)
X_test_scaled = pd.DataFrame(X_test_scaled, columns=feature_names)

print(X_test_scaled)

###########################################################################################
rf = RandomForestClassifier(n_estimators=100, random_state = 21)
rf.fit(X_train_scaled, y_train)
y_pred = rf.predict(X_test_scaled)

print("Accuracy:", accuracy_score(y_test, y_pred))
print("\n -------------Klassifikations rapport-------------\n")
print(classification_report(y_test, y_pred))

labels = ['Knock', 'Noise']
cm = confusion_matrix(y_test, y_pred)
sns.heatmap(
    cm, 
    xticklabels=labels, 
    yticklabels=labels, 
    annot=True,
    linewidths = 0.1, 
    fmt="d", 
    cmap = 'YlGnBu')

plt.title("Confusion matrix Full", fontsize = 15)
plt.ylabel('True label')
plt.xlabel('Predicted label')
plt.show()

###########################################################################################
feature_importances = pd.DataFrame(
    rf.feature_importances_,
    index = X_train_scaled.columns,
    columns=['importance']).sort_values('importance', ascending=False)

feature_importances 

###########################################################################################
top_features = feature_importances.index[[8,11,15,1]]
X_train_sel = X_train_scaled[top_features]
X_test_sel = X_test_scaled[top_features]

rf2 = RandomForestClassifier(random_state=21, n_estimators=100)
rf2.fit(X_train_sel, y_train)
y_pred = rf2.predict(X_test_sel)
print("Accuracy:", accuracy_score(y_test, y_pred))
print("Accuracy:", f1_score(y_test, y_pred, average='macro'))
print("Features: ", top_features)

###########################################################################################
print("Accuracy:", accuracy_score(y_test, y_pred))
print("\n -------------Classification Report-------------\n")
print(classification_report(y_test, y_pred))

labels = ['Knock', 'Noise']
cm2 = confusion_matrix(y_test, y_pred)
plt.figure(figsize = (3,2))
sns.heatmap(
    cm2, 
    xticklabels=labels, 
    yticklabels=labels, 
    annot=True,
    linewidths = 0.1, 
    fmt="d", 
    cmap = 'YlGnBu')

plt.title("Confusion matrix Full", fontsize = 15)
plt.ylabel('True label')
plt.xlabel('Predicted label')
plt.show()

###########################################################################################
for n_est in [9, 10, 20, 50, 100]:
    rf_test = RandomForestClassifier(
        n_estimators=n_est,
        random_state=42)
    rf_test.fit(X_train_sel, y_train)
    y_pred_test = rf_test.predict(X_test_sel)
    print(f"n_estimators={n_est}: Acc={accuracy_score(y_test, y_pred_test):.3f}")

###########################################################################################
rf_final = RandomForestClassifier(n_estimators=9, random_state=42)
rf_final.fit(X_train_sel, y_train)

###########################################################################################
features_idx = []

for i, feat in enumerate(top_features):
    orig_idx = feature_names.index(feat)
    features_idx.append(orig_idx)   # Gem indekser

scaler_means = scaler.mean_[features_idx]
scaler_scales = scaler.scale_[features_idx]

# Generer header fil med scaler parametre
header_content = f"""
#pragma once

const float SCALER_MEAN[4] = {{
    {scaler_means[0]:.10e}f,  // x_energy
    {scaler_means[1]:.10e}f,  // x_pos_count
    {scaler_means[2]:.10e}f,  // x_above_mean
    {scaler_means[3]:.10e}f   // x_argmax
}};

const float SCALER_SCALE[4] = {{
    {scaler_scales[0]:.10e}f,  // x_energy
    {scaler_scales[1]:.10e}f,  // x_pos_count
    {scaler_scales[2]:.10e}f,  // x_above_mean
    {scaler_scales[3]:.10e}f   // x_argmax
}};
"""

with open('feature_scaler.h', 'w') as f:
    f.write(header_content)

###########################################################################################
# Convert RandomForest til C
cmodel = emlearn.convert(rf_final, method='inline', dtype='float')
cmodel.save(file='knock_detector_FLOAT.h')