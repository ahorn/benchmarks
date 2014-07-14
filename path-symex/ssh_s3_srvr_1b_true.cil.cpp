int nse_symbolic_int();
void nse_assert(bool);

// This is a further simplified version of s3_srvr_1a.cil.c
int main() {
  int s__state ;
  int s__hit = nse_symbolic_int() ;
  int blastFlag ;
  int tmp___1;

  s__state = 8466;
  blastFlag = 0;

  for (int i = 0; i < 42; ++i) {
	  nse_assert(s__state > 8512 || blastFlag <= 2);
              {
                {
                  {
                    {
                      {
                        if (s__state == 8466) {
                          goto switch_1_8466;
                        } else {
                          {
                            {
                              if (s__state == 8512) {
                                goto switch_1_8512;
                              } else {
                                {
                                  {
                                    {
                                      {
                                        {
                                          {
                                            {
                                                {
                                                  {
                                                    {
                                                      {
                                                        {
                                                          {
                                                            if (s__state == 8640) {
                                                              goto switch_1_8640;
                                                            } else {
                                                              {
                                                                if (s__state == 8656) {
                                                                  goto switch_1_8656;
                                                                } else {
                                                                  {
                                                                    {
                                                                      goto end;

                                                                          switch_1_8466:
                                                                            if (blastFlag == 0) {
                                                                              blastFlag = 2;
                                                                            }
                                                                            if (s__hit) {
                                                                              s__state = 8656;
                                                                            } else {
                                                                              s__state = 8512;
                                                                            }
                                                                            goto switch_1_break;

                                                                          switch_1_8512:
                                                                            tmp___1 = nse_symbolic_int();
                                                                            if (tmp___1) {
                                                                              s__state = 8466;
                                                                            } else {
                                                                              s__state = 8640;
                                                                            }
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
