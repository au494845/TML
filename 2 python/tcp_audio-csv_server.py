import socket
import csv
import os

OUTPUT_DIR = 'test'
ACTION = 'noise'
HOST = '0.0.0.0'
PORT = 7123
SAMPLERATE = 8000

os.makedirs(OUTPUT_DIR, exist_ok=True)

def get_unique_output_path():
    for i in range(1, 1000):
        path = os.path.join(OUTPUT_DIR, f"{i:04d}.csv")
        if not os.path.exists(path):
            return path
        
    return os.path.join(OUTPUT_DIR, "0000.csv")

def main():
    with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as s:
        s.bind((HOST, PORT))
        s.listen(1)
        s.settimeout(1.0)
        print(f"Lytter på port {PORT} for audio-data...")
        try:
            while True:
                try:
                    conn, addr = s.accept()
                except socket.timeout:
                    continue
                print(f"Forbindelse fra {addr}")
                out_path = get_unique_output_path()
                with conn, open(out_path, 'w', newline='') as csvfile:
                    writer = csv.writer(csvfile)
                    writer.writerow(['action', 'timestamp', 'samplevalue'])
                    
                    sample_count = 0
                    
                    while True:
                        data = conn.recv(4096)
                        if not data:
                            break
                        for byte in data:
                            timestamp = sample_count / SAMPLERATE
                            writer.writerow([ACTION, timestamp, byte])
                            sample_count += 1
                print(f"Transmission færdig, gemt til {out_path}")
        except KeyboardInterrupt:
            print("\nServeren blev stoppet med Ctrl+C.")

if __name__ == "__main__":
    main()