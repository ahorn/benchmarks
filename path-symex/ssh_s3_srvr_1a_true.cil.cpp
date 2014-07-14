typedef unsigned long ulong;

ulong nse_symbolic_ulong();
int nse_symbolic_int();
void nse_assert(bool);

// This is a simplified version of s3_srvr_1.cil.c
int main() {
  int s__state ;
  int s__hit = nse_symbolic_int() ;
  int s__verify_mode = nse_symbolic_int() ;
  int s__session__peer = nse_symbolic_int() ;
  ulong s__s3__tmp__new_cipher__algorithms = nse_symbolic_ulong() ;
  int buf ;
  int cb ;
  int blastFlag ;
  int tmp___1;

  s__state = 8466;
  blastFlag = 0;

  for (int i = 0; i < 12; ++i) {
             nse_assert (s__state > 8512 || blastFlag <= 2);
              {
                {
                  {
                    {
                      {
                        if (s__state == 8466) {
                          goto switch_1_8466;
                        } else {
                          if (s__state == 8496) {
                            goto switch_1_8496;
                          } else {
                            {
                              if (s__state == 8512) {
                                goto switch_1_8512;
                              } else {
                                {
                                  if (s__state == 8528) {
                                    goto switch_1_8528;
                                  } else {
                                    {
                                      if (s__state == 8544) {
                                        goto switch_1_8544;
                                      } else {
                                        {
                                          if (s__state == 8560) {
                                            goto switch_1_8560;
                                          } else {
                                            {
                                                if (s__state == 8576) {
                                                  goto switch_1_8576;
                                                } else {
                                                  {
                                                    if (s__state == 8592) {
                                                      goto switch_1_8592;
                                                    } else {
                                                      {
                                                        if (s__state == 8608) {
                                                          goto switch_1_8608;
                                                        } else {
                                                          {
                                                            if (s__state == 8640) {
                                                              goto switch_1_8640;
                                                            } else {
                                                              {
                                                                if (s__state == 8656) {
                                                                  goto switch_1_8656;
                                                                } else {
                                                                  {
                                                                    if (s__state == 8672) {
                                                                      goto switch_1_8672;
                                                                    } else {
                                                                      goto end;

                                                                          switch_1_8466:
                                                                            if (blastFlag == 0) {
                                                                              blastFlag = 1;
                                                                            }
                                                                            s__state = 8496;
                                                                            goto switch_1_break;

                                                                          switch_1_8496:
                                                                            if (blastFlag == 1) {
                                                                              blastFlag = 2;
                                                                            }
                                                                            if (s__hit) {
                                                                              s__state = 8656;
                                                                            } else {
                                                                              s__state = 8512;
                                                                            }
                                                                            goto switch_1_break;

                                                                          switch_1_8512:
                                                                            s__state = 8528;
                                                                            goto switch_1_break;

                                                                          switch_1_8528:
                                                                            s__state = 8544;
                                                                            goto switch_1_break;

                                                                          switch_1_8544:
                                                                            if (s__verify_mode + 1) {
                                                                              if (s__session__peer != 0) {
                                                                                if (s__verify_mode + 4) {
                                                                                  s__state = 8560;
                                                                                } else {
                                                                                  goto _L___2;
                                                                                }
                                                                              } else {
                                                                                _L___2:
                                                                                if (s__s3__tmp__new_cipher__algorithms + 256UL) {
                                                                                  if (s__verify_mode + 2) {
                                                                                    goto _L___1;
                                                                                  } else {
                                                                                    s__state = 8560;
                                                                                  }
                                                                                } else {
                                                                                  _L___1:
                                                                                  s__state = 8576;
                                                                                }
                                                                              }
                                                                            } else {
                                                                              s__state = 8560;
                                                                            }
                                                                            goto switch_1_break;

                                                                          switch_1_8560:
                                                                            s__state = 8576;
                                                                            goto switch_1_break;

                                                                          switch_1_8576:
                                                                            tmp___1 = nse_symbolic_int();
                                                                            if (tmp___1 == 2) {
                                                                              s__state = 8466;
                                                                            } else {
                                                                              s__state = 8592;
                                                                            }
                                                                            goto switch_1_break;

                                                                          switch_1_8592:
                                                                            s__state = 8608;
                                                                            goto switch_1_break;

                                                                          switch_1_8608:
                                                                            s__state = 8640;
                                                                            goto switch_1_break;

                                                                          switch_1_8640:
                                                                            if (blastFlag == 3) {
                                                                              blastFlag = 4;
                                                                            }
                                                                            if (s__hit) {
                                                                              goto end;
                                                                            } else {
                                                                              s__state = 8656;
                                                                            }
                                                                            goto switch_1_break;

                                                                          switch_1_8656:
                                                                            if (blastFlag == 2) {
                                                                              blastFlag = 3;
                                                                            }
                                                                            s__state = 8672;
                                                                            goto switch_1_break;

                                                                          switch_1_8672:
                                                                            if (blastFlag == 4) {
                                                                              blastFlag = 5;
                                                                            } else {
                                                                              nse_assert(blastFlag != 5);
                                                                            }
                                                                            if (s__hit) {
                                                                              s__state = 8640;
                                                                            } else {
                                                                              goto end;
                                                                            }
                                                                            goto switch_1_break;

                                                                    }
                                                                  }
                                                                }
                                                              }
                                                            }
                                                          }
                                                        }
                                                      }
                                                    }
                                                  }
                                                }
                                            }
                                          }
                                        }
                                      }
                                    }
                                  }
                                }
                              }
                            }
                          }
                        }
                      }
                    }
                  }
                }
              }
  switch_1_break: ;
  }

  end:
  return (-1);
}
