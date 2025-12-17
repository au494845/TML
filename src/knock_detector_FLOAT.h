


    // !!! This file is generated using emlearn !!!

    #include <stdint.h>
    

static inline int32_t knock_detector_FLOAT_tree_0(const float *features, int32_t features_length) {
          if (features[3] < -0.461764f) {
              if (features[0] < -0.503460f) {
                  return 1;
              } else {
                  if (features[0] < 1.556273f) {
                      if (features[3] < -0.737776f) {
                          if (features[2] < 0.907025f) {
                              return 0;
                          } else {
                              return 1;
                          }
                      } else {
                          if (features[2] < -0.961343f) {
                              return 1;
                          } else {
                              if (features[0] < 0.228703f) {
                                  return 1;
                              } else {
                                  return 0;
                              }
                          }
                      }
                  } else {
                      return 1;
                  }
              }
          } else {
              if (features[2] < 0.424010f) {
                  return 0;
              } else {
                  if (features[0] < -0.218798f) {
                      if (features[3] < 1.304411f) {
                          return 0;
                      } else {
                          return 1;
                      }
                  } else {
                      return 1;
                  }
              }
          }
        }
        

static inline int32_t knock_detector_FLOAT_tree_1(const float *features, int32_t features_length) {
          if (features[3] < 0.229774f) {
              if (features[3] < -0.827141f) {
                  return 1;
              } else {
                  if (features[2] < 0.456615f) {
                      if (features[2] < -0.590803f) {
                          if (features[2] < -2.205405f) {
                              return 1;
                          } else {
                              return 0;
                          }
                      } else {
                          return 1;
                      }
                  } else {
                      if (features[2] < 0.746779f) {
                          if (features[1] < -0.321620f) {
                              return 0;
                          } else {
                              if (features[0] < 1.171693f) {
                                  return 0;
                              } else {
                                  return 1;
                              }
                          }
                      } else {
                          if (features[2] < 0.887311f) {
                              return 1;
                          } else {
                              if (features[3] < -0.809796f) {
                                  return 1;
                              } else {
                                  return 0;
                              }
                          }
                      }
                  }
              }
          } else {
              if (features[0] < -0.527958f) {
                  return 1;
              } else {
                  if (features[1] < 1.335532f) {
                      return 0;
                  } else {
                      if (features[1] < 1.421719f) {
                          return 1;
                      } else {
                          return 0;
                      }
                  }
              }
          }
        }
        

static inline int32_t knock_detector_FLOAT_tree_2(const float *features, int32_t features_length) {
          if (features[0] < -0.554788f) {
              return 1;
          } else {
              if (features[3] < -0.813189f) {
                  if (features[3] < -0.828272f) {
                      return 1;
                  } else {
                      if (features[2] < 0.518035f) {
                          return 1;
                      } else {
                          return 0;
                      }
                  }
              } else {
                  if (features[0] < 1.597118f) {
                      if (features[3] < 0.016355f) {
                          if (features[2] < 0.193497f) {
                              if (features[0] < 0.113675f) {
                                  return 1;
                              } else {
                                  return 0;
                              }
                          } else {
                              return 0;
                          }
                      } else {
                          if (features[3] < 1.031039f) {
                              return 0;
                          } else {
                              if (features[2] < 0.350458f) {
                                  return 0;
                              } else {
                                  return 1;
                              }
                          }
                      }
                  } else {
                      return 1;
                  }
              }
          }
        }
        

static inline int32_t knock_detector_FLOAT_tree_3(const float *features, int32_t features_length) {
          if (features[1] < 0.372451f) {
              if (features[0] < -0.513884f) {
                  if (features[2] < 1.126670f) {
                      if (features[3] < -0.085452f) {
                          return 1;
                      } else {
                          return 0;
                      }
                  } else {
                      if (features[0] < -0.568642f) {
                          return 1;
                      } else {
                          return 0;
                      }
                  }
              } else {
                  if (features[0] < -0.253894f) {
                      if (features[2] < 1.000798f) {
                          if (features[0] < -0.349511f) {
                              return 0;
                          } else {
                              if (features[1] < 0.086465f) {
                                  return 1;
                              } else {
                                  return 0;
                              }
                          }
                      } else {
                          return 1;
                      }
                  } else {
                      return 1;
                  }
              }
          } else {
              if (features[3] < 0.063488f) {
                  if (features[2] < -0.590803f) {
                      if (features[0] < -0.054488f) {
                          return 1;
                      } else {
                          return 0;
                      }
                  } else {
                      return 1;
                  }
              } else {
                  return 0;
              }
          }
        }
        

static inline int32_t knock_detector_FLOAT_tree_4(const float *features, int32_t features_length) {
          if (features[3] < -0.746826f) {
              if (features[1] < 1.255221f) {
                  if (features[2] < 0.671205f) {
                      return 1;
                  } else {
                      if (features[1] < -0.664412f) {
                          if (features[0] < -0.550582f) {
                              return 1;
                          } else {
                              if (features[0] < -0.534489f) {
                                  return 0;
                              } else {
                                  return 1;
                              }
                          }
                      } else {
                          return 0;
                      }
                  }
              } else {
                  return 0;
              }
          } else {
              if (features[3] < 1.681854f) {
                  if (features[2] < 0.517529f) {
                      return 0;
                  } else {
                      if (features[2] < 0.552157f) {
                          return 1;
                      } else {
                          return 0;
                      }
                  }
              } else {
                  if (features[3] < 2.604157f) {
                      return 1;
                  } else {
                      return 0;
                  }
              }
          }
        }
        

static inline int32_t knock_detector_FLOAT_tree_5(const float *features, int32_t features_length) {
          if (features[3] < -0.461764f) {
              if (features[2] < -0.003147f) {
                  if (features[0] < 0.153404f) {
                      return 1;
                  } else {
                      return 0;
                  }
              } else {
                  if (features[0] < -0.505590f) {
                      return 1;
                  } else {
                      if (features[1] < -0.321620f) {
                          if (features[1] < -0.813281f) {
                              return 1;
                          } else {
                              return 0;
                          }
                      } else {
                          return 1;
                      }
                  }
              }
          } else {
              if (features[2] < -0.088325f) {
                  if (features[2] < -0.118403f) {
                      return 0;
                  } else {
                      return 1;
                  }
              } else {
                  if (features[0] < -0.506655f) {
                      if (features[1] < -1.383294f) {
                          return 0;
                      } else {
                          if (features[3] < 0.409258f) {
                              return 1;
                          } else {
                              if (features[2] < 0.591839f) {
                                  return 1;
                              } else {
                                  return 0;
                              }
                          }
                      }
                  } else {
                      return 0;
                  }
              }
          }
        }
        

static inline int32_t knock_detector_FLOAT_tree_6(const float *features, int32_t features_length) {
          if (features[0] < -0.516388f) {
              if (features[2] < 0.887311f) {
                  return 1;
              } else {
                  if (features[3] < -0.816960f) {
                      return 1;
                  } else {
                      return 0;
                  }
              }
          } else {
              if (features[3] < 0.016355f) {
                  if (features[3] < -0.829403f) {
                      return 1;
                  } else {
                      if (features[3] < -0.759646f) {
                          if (features[2] < 0.782923f) {
                              return 0;
                          } else {
                              return 1;
                          }
                      } else {
                          if (features[3] < -0.461764f) {
                              return 1;
                          } else {
                              if (features[1] < 0.592491f) {
                                  return 0;
                              } else {
                                  return 1;
                              }
                          }
                      }
                  }
              } else {
                  if (features[2] < 0.420724f) {
                      return 0;
                  } else {
                      if (features[3] < 0.922821f) {
                          return 0;
                      } else {
                          return 1;
                      }
                  }
              }
          }
        }
        

static inline int32_t knock_detector_FLOAT_tree_7(const float *features, int32_t features_length) {
          if (features[0] < -0.516388f) {
              if (features[3] < -0.616361f) {
                  if (features[0] < -0.549398f) {
                      return 1;
                  } else {
                      if (features[2] < 0.833979f) {
                          return 1;
                      } else {
                          return 0;
                      }
                  }
              } else {
                  if (features[2] < 1.011413f) {
                      if (features[3] < 0.409258f) {
                          return 1;
                      } else {
                          if (features[1] < -0.335985f) {
                              return 0;
                          } else {
                              return 1;
                          }
                      }
                  } else {
                      return 0;
                  }
              }
          } else {
              if (features[0] < 1.540444f) {
                  if (features[1] < 2.042662f) {
                      if (features[3] < -0.804140f) {
                          if (features[1] < 0.087118f) {
                              return 0;
                          } else {
                              return 1;
                          }
                      } else {
                          if (features[3] < 1.032170f) {
                              if (features[3] < -0.404073f) {
                                  if (features[0] < 0.028456f) {
                                      if (features[0] < -0.224123f) {
                                          return 0;
                                      } else {
                                          return 1;
                                      }
                                  } else {
                                      return 0;
                                  }
                              } else {
                                  return 0;
                              }
                          } else {
                              if (features[2] < 0.420724f) {
                                  return 0;
                              } else {
                                  return 1;
                              }
                          }
                      }
                  } else {
                      return 1;
                  }
              } else {
                  return 1;
              }
          }
        }
        

static inline int32_t knock_detector_FLOAT_tree_8(const float *features, int32_t features_length) {
          if (features[0] < -0.516388f) {
              if (features[2] < 0.887311f) {
                  return 1;
              } else {
                  if (features[3] < -0.816960f) {
                      return 1;
                  } else {
                      return 0;
                  }
              }
          } else {
              if (features[2] < 0.553926f) {
                  if (features[3] < -0.461764f) {
                      if (features[2] < 0.469253f) {
                          if (features[0] < 1.597118f) {
                              if (features[3] < -0.737776f) {
                                  if (features[3] < -0.786418f) {
                                      return 1;
                                  } else {
                                      return 0;
                                  }
                              } else {
                                  return 1;
                              }
                          } else {
                              return 1;
                          }
                      } else {
                          if (features[1] < -0.140757f) {
                              return 1;
                          } else {
                              return 0;
                          }
                      }
                  } else {
                      if (features[2] < 0.479616f) {
                          if (features[3] < 1.923176f) {
                              return 0;
                          } else {
                              if (features[0] < -0.362258f) {
                                  return 1;
                              } else {
                                  return 0;
                              }
                          }
                      } else {
                          return 1;
                      }
                  }
              } else {
                  return 0;
              }
          }
        }
        

int32_t knock_detector_FLOAT_predict(const float *features, int32_t features_length) {

        int32_t votes[2] = {0,};
        int32_t _class = -1;

        _class = knock_detector_FLOAT_tree_0(features, features_length); votes[_class] += 1;
    _class = knock_detector_FLOAT_tree_1(features, features_length); votes[_class] += 1;
    _class = knock_detector_FLOAT_tree_2(features, features_length); votes[_class] += 1;
    _class = knock_detector_FLOAT_tree_3(features, features_length); votes[_class] += 1;
    _class = knock_detector_FLOAT_tree_4(features, features_length); votes[_class] += 1;
    _class = knock_detector_FLOAT_tree_5(features, features_length); votes[_class] += 1;
    _class = knock_detector_FLOAT_tree_6(features, features_length); votes[_class] += 1;
    _class = knock_detector_FLOAT_tree_7(features, features_length); votes[_class] += 1;
    _class = knock_detector_FLOAT_tree_8(features, features_length); votes[_class] += 1;
    
        int32_t most_voted_class = -1;
        int32_t most_voted_votes = 0;
        for (int32_t i=0; i<2; i++) {

            if (votes[i] > most_voted_votes) {
                most_voted_class = i;
                most_voted_votes = votes[i];
            }
        }
        return most_voted_class;
    }
    

int knock_detector_FLOAT_predict_proba(const float *features, int32_t features_length, float *out, int out_length) {

        int32_t _class = -1;

        for (int i=0; i<out_length; i++) {
            out[i] = 0.0f;
        }

        _class = knock_detector_FLOAT_tree_0(features, features_length); out[_class] += 1.0f;
    _class = knock_detector_FLOAT_tree_1(features, features_length); out[_class] += 1.0f;
    _class = knock_detector_FLOAT_tree_2(features, features_length); out[_class] += 1.0f;
    _class = knock_detector_FLOAT_tree_3(features, features_length); out[_class] += 1.0f;
    _class = knock_detector_FLOAT_tree_4(features, features_length); out[_class] += 1.0f;
    _class = knock_detector_FLOAT_tree_5(features, features_length); out[_class] += 1.0f;
    _class = knock_detector_FLOAT_tree_6(features, features_length); out[_class] += 1.0f;
    _class = knock_detector_FLOAT_tree_7(features, features_length); out[_class] += 1.0f;
    _class = knock_detector_FLOAT_tree_8(features, features_length); out[_class] += 1.0f;
    
        // compute mean
        for (int i=0; i<out_length; i++) {
            out[i] = out[i] / 9;
        }
        return 0;
    }
    