typedef unsigned long ulong;

long nse_symbolic_long();
ulong nse_symbolic_ulong();
int nse_symbolic_int();

void nse_assert(bool);

#line 4 "s3_srvr_2_BUG.cil.c"
int ssl3_accept(int initial_state ) 
{ int s__info_callback = nse_symbolic_int() ;
  int s__in_handshake = nse_symbolic_int() ;
  int s__state ;
  int s__new_session ;
  int s__server ;
  int s__version = nse_symbolic_int() ;
  int s__type ;
  int s__init_num ;
  int s__hit = nse_symbolic_int() ;
  int s__rwstate ;
  int s__init_buf___0 ;
  int s__debug = nse_symbolic_int() ;
  int s__shutdown ;
  int s__cert = nse_symbolic_int() ;
  int s__options = nse_symbolic_int() ;
  int s__verify_mode = nse_symbolic_int() ;
  int s__session__peer = nse_symbolic_int() ;
  int s__cert__pkeys__AT0__privatekey = nse_symbolic_int() ;
  int s__ctx__info_callback = nse_symbolic_int() ;
  int s__ctx__stats__sess_accept_renegotiate = nse_symbolic_int() ;
  int s__ctx__stats__sess_accept = nse_symbolic_int() ;
  int s__ctx__stats__sess_accept_good = nse_symbolic_int() ;
  int s__s3__tmp__cert_request ;
  int s__s3__tmp__reuse_message = nse_symbolic_int() ;
  int s__s3__tmp__use_rsa_tmp ;
  int s__s3__tmp__new_cipher = nse_symbolic_int() ;
  int s__s3__tmp__new_cipher__algorithms = nse_symbolic_int() ;
  int s__s3__tmp__next_state___0 ;
  int s__s3__tmp__new_cipher__algo_strength = nse_symbolic_int() ;
  int s__session__cipher ;
  int buf ;
  ulong l ;
  ulong Time ;
  ulong tmp ;
  int cb ;
  long num1 ;
  int ret ;
  int new_state ;
  int state ;
  int skip ;
  int got_new_session ;
  int tmp___1 = nse_symbolic_int() ;
  int tmp___2 = nse_symbolic_int() ;
  int tmp___3 = nse_symbolic_int() ;
  int tmp___4 = nse_symbolic_int() ;
  int tmp___5 = nse_symbolic_int() ;
  int tmp___6 = nse_symbolic_int() ;
  int tmp___7 ;
  long tmp___8 = nse_symbolic_long() ;
  int tmp___9 = nse_symbolic_int() ;
  int tmp___10 = nse_symbolic_int() ;
  int blastFlag ;
  int __cil_tmp55 ;
  ulong __cil_tmp56 ;
  ulong __cil_tmp57 ;
  ulong __cil_tmp58 ;
  ulong __cil_tmp59 ;
  int __cil_tmp60 ;
  ulong __cil_tmp61 ;

  {
#line 60
;
  s__state = initial_state;
#line 61
  blastFlag = 0;
#line 62
  tmp = nse_symbolic_ulong();
#line 63
  Time = tmp;
#line 64
  cb = 0;
#line 65
  ret = -1;
#line 66
  skip = 0;
#line 67
  got_new_session = 0;
#line 68
  if (s__info_callback != 0) {
#line 69
    cb = s__info_callback;
  } else {
#line 71
    if (s__ctx__info_callback != 0) {
#line 72
      cb = s__ctx__info_callback;
    }
  }
#line 77
  s__in_handshake ++;
#line 78
  if (tmp___1 + 12288) {
#line 79
    if (tmp___2 + 16384) {

    }
  }
#line 87
  if (s__cert == 0) {
#line 88
    return (-1);
  }
  {
#line 93
  for (int i = 0; i < 4; ++i) {
    while_0_continue: /* CIL Label */ ;
#line 95
    state = s__state;
#line 96
    if (s__state == 12292) {
      goto switch_1_12292;
    } else {
#line 99
      if (s__state == 16384) {
        goto switch_1_16384;
      } else {
#line 102
        if (s__state == 8192) {
          goto switch_1_8192;
        } else {
#line 105
          if (s__state == 24576) {
            goto switch_1_24576;
          } else {
#line 108
            if (s__state == 8195) {
              goto switch_1_8195;
            } else {
#line 111
              if (s__state == 8480) {
                goto switch_1_8480;
              } else {
#line 114
                if (s__state == 8481) {
                  goto switch_1_8481;
                } else {
#line 117
                  if (s__state == 8482) {
                    goto switch_1_8482;
                  } else {
#line 120
                    if (s__state == 8464) {
                      goto switch_1_8464;
                    } else {
#line 123
                      if (s__state == 8465) {
                        goto switch_1_8465;
                      } else {
#line 126
                        if (s__state == 8466) {
                          goto switch_1_8466;
                        } else {
#line 129
                          if (s__state == 8496) {
                            goto switch_1_8496;
                          } else {
#line 132
                            if (s__state == 8497) {
                              goto switch_1_8497;
                            } else {
#line 135
                              if (s__state == 8512) {
                                goto switch_1_8512;
                              } else {
#line 138
                                if (s__state == 8513) {
                                  goto switch_1_8513;
                                } else {
#line 141
                                  if (s__state == 8528) {
                                    goto switch_1_8528;
                                  } else {
#line 144
                                    if (s__state == 8529) {
                                      goto switch_1_8529;
                                    } else {
#line 147
                                      if (s__state == 8544) {
                                        goto switch_1_8544;
                                      } else {
#line 150
                                        if (s__state == 8545) {
                                          goto switch_1_8545;
                                        } else {
#line 153
                                          if (s__state == 8560) {
                                            goto switch_1_8560;
                                          } else {
#line 156
                                            if (s__state == 8561) {
                                              goto switch_1_8561;
                                            } else {
#line 159
                                              if (s__state == 8448) {
                                                goto switch_1_8448;
                                              } else {
#line 162
                                                if (s__state == 8576) {
                                                  goto switch_1_8576;
                                                } else {
#line 165
                                                  if (s__state == 8577) {
                                                    goto switch_1_8577;
                                                  } else {
#line 168
                                                    if (s__state == 8592) {
                                                      goto switch_1_8592;
                                                    } else {
#line 171
                                                      if (s__state == 8593) {
                                                        goto switch_1_8593;
                                                      } else {
#line 174
                                                        if (s__state == 8608) {
                                                          goto switch_1_8608;
                                                        } else {
#line 177
                                                          if (s__state == 8609) {
                                                            goto switch_1_8609;
                                                          } else {
#line 180
                                                            if (s__state == 8640) {
                                                              goto switch_1_8640;
                                                            } else {
#line 183
                                                              if (s__state == 8641) {
                                                                goto switch_1_8641;
                                                              } else {
#line 186
                                                                if (s__state == 8656) {
                                                                  goto switch_1_8656;
                                                                } else {
#line 189
                                                                  if (s__state == 8657) {
                                                                    goto switch_1_8657;
                                                                  } else {
#line 192
                                                                    if (s__state == 8672) {
                                                                      goto switch_1_8672;
                                                                    } else {
#line 195
                                                                      if (s__state == 8673) {
                                                                        goto switch_1_8673;
                                                                      } else {
#line 198
                                                                        if (s__state == 3) {
                                                                          goto switch_1_3;
                                                                        } else {
                                                                          goto switch_1_default;
#line 203
                                                                          if (0) {
                                                                            switch_1_12292: 
#line 205
                                                                            s__new_session = 1;
                                                                            switch_1_16384: ;
                                                                            switch_1_8192: ;
                                                                            switch_1_24576: ;
                                                                            switch_1_8195: 
#line 210
                                                                            s__server = 1;
#line 211
                                                                            if (cb != 0) {

                                                                            }
                                                                            {
#line 216
                                                                            __cil_tmp55 = s__version * 8;
#line 216
                                                                            if (__cil_tmp55 != 3) {
#line 217
                                                                              return (-1);
                                                                            }
                                                                            }
#line 221
                                                                            s__type = 8192;
#line 222
                                                                            if (s__init_buf___0 == 0) {
#line 223
                                                                              buf = nse_symbolic_int();
#line 224
                                                                              if (buf == 0) {
#line 225
                                                                                ret = -1;
                                                                                goto end;
                                                                              }
#line 230
                                                                              if (! tmp___3) {
#line 231
                                                                                ret = -1;
                                                                                goto end;
                                                                              }
#line 236
                                                                              s__init_buf___0 = buf;
                                                                            }
#line 240
                                                                            if (! tmp___4) {
#line 241
                                                                              ret = -1;
                                                                              goto end;
                                                                            }
#line 246
                                                                            s__init_num = 0;
#line 247
                                                                            if (s__state != 12292) {
#line 248
                                                                              if (! tmp___5) {
#line 249
                                                                                ret = -1;
                                                                                goto end;
                                                                              }
#line 254
                                                                              s__state = 8464;
#line 255
                                                                              s__ctx__stats__sess_accept ++;
                                                                            } else {
#line 257
                                                                              s__ctx__stats__sess_accept_renegotiate ++;
#line 258
                                                                              s__state = 8480;
                                                                            }
                                                                            goto switch_1_break;
                                                                            switch_1_8480: ;
                                                                            switch_1_8481: 
#line 263
                                                                            s__shutdown = 0;
#line 264
                                                                            ret = nse_symbolic_int();
#line 265
                                                                            if (ret <= 0) {
                                                                              goto end;
                                                                            }
#line 270
                                                                            s__s3__tmp__next_state___0 = 8482;
#line 271
                                                                            s__state = 8448;
#line 272
                                                                            s__init_num = 0;
                                                                            goto switch_1_break;
                                                                            switch_1_8482: 
#line 275
                                                                            s__state = 3;
                                                                            goto switch_1_break;
                                                                            switch_1_8464: ;
                                                                            switch_1_8465: ;
                                                                            switch_1_8466: 
#line 280
                                                                            s__shutdown = 0;
#line 281
                                                                            ret = nse_symbolic_int();
#line 282
                                                                            if (blastFlag == 0) {
#line 283
                                                                              blastFlag = 1;
                                                                            }
#line 287
                                                                            if (ret <= 0) {
                                                                              goto end;
                                                                            }
#line 292
                                                                            got_new_session = 1;
#line 293
                                                                            s__state = 8496;
#line 294
                                                                            s__init_num = 0;
                                                                            goto switch_1_break;
                                                                            switch_1_8496: ;
                                                                            switch_1_8497: 
#line 298
                                                                            ret = nse_symbolic_int();
#line 299
                                                                            if (blastFlag == 1) {
#line 300
                                                                              blastFlag = 2;
                                                                            } else {
#line 302
                                                                              if (blastFlag == 3) {
#line 303
                                                                                blastFlag = 4;
                                                                              }
                                                                            }
#line 308
                                                                            if (ret <= 0) {
                                                                              goto end;
                                                                            }
#line 313
                                                                            if (s__hit) {
#line 314
                                                                              s__state = 8656;
                                                                            } else {
#line 316
                                                                              s__state = 8512;
                                                                            }
#line 318
                                                                            s__init_num = 0;
                                                                            goto switch_1_break;
                                                                            switch_1_8512: ;
                                                                            switch_1_8513: ;
                                                                            {
#line 322
                                                                            __cil_tmp56 = (ulong )s__s3__tmp__new_cipher__algorithms;
#line 322
                                                                            if (__cil_tmp56 + 256UL) {
#line 323
                                                                              skip = 1;
                                                                            } else {
#line 325
                                                                              ret = nse_symbolic_int();
#line 326
                                                                              if (ret <= 0) {
                                                                                goto end;
                                                                              }
                                                                            }
                                                                            }
#line 332
                                                                            s__state = 8528;
#line 333
                                                                            s__init_num = 0;
                                                                            goto switch_1_break;
                                                                            switch_1_8528: ;
                                                                            switch_1_8529: 
#line 337
                                                                            l = (ulong )s__s3__tmp__new_cipher__algorithms;
                                                                            {
#line 338
                                                                            __cil_tmp57 = (ulong )s__options;
#line 338
                                                                            if (__cil_tmp57 + 2097152UL) {
#line 339
                                                                              s__s3__tmp__use_rsa_tmp = 1;
                                                                            } else {
#line 341
                                                                              s__s3__tmp__use_rsa_tmp = 0;
                                                                            }
                                                                            }
#line 343
                                                                            if (s__s3__tmp__use_rsa_tmp) {
                                                                              goto _L___0;
                                                                            } else {
#line 346
                                                                              if (l + 30UL) {
                                                                                goto _L___0;
                                                                              } else {
#line 349
                                                                                if (l + 1UL) {
#line 350
                                                                                  if (s__cert__pkeys__AT0__privatekey == 0) {
                                                                                    goto _L___0;
                                                                                  } else {
                                                                                    {
#line 353
                                                                                    __cil_tmp58 = (ulong )s__s3__tmp__new_cipher__algo_strength;
#line 353
                                                                                    if (__cil_tmp58 + 2UL) {
                                                                                      {
#line 354
                                                                                      __cil_tmp59 = (ulong )s__s3__tmp__new_cipher__algo_strength;
#line 354
                                                                                      if (__cil_tmp59 + 4UL) {
#line 355
                                                                                        tmp___7 = 512;
                                                                                      } else {
#line 357
                                                                                        tmp___7 = 1024;
                                                                                      }
                                                                                      }
                                                                                      {
#line 359
                                                                                      __cil_tmp60 = tmp___6 * 8;
#line 359
                                                                                      if (__cil_tmp60 > tmp___7) {
                                                                                        _L___0: 
#line 361
                                                                                        ret = nse_symbolic_int();
#line 362
                                                                                        if (ret <= 0) {
                                                                                          goto end;
                                                                                        }
                                                                                      } else {
#line 368
                                                                                        skip = 1;
                                                                                      }
                                                                                      }
                                                                                    } else {
#line 371
                                                                                      skip = 1;
                                                                                    }
                                                                                    }
                                                                                  }
                                                                                } else {
#line 375
                                                                                  skip = 1;
                                                                                }
                                                                              }
                                                                            }
#line 379
                                                                            s__state = 8544;
#line 380
                                                                            s__init_num = 0;
                                                                            goto switch_1_break;
                                                                            switch_1_8544: ;
                                                                            switch_1_8545: ;
#line 384
                                                                            if (s__verify_mode + 1) {
#line 385
                                                                              if (s__session__peer != 0) {
#line 386
                                                                                if (s__verify_mode + 4) {
#line 387
                                                                                  skip = 1;
#line 388
                                                                                  s__s3__tmp__cert_request = 0;
#line 389
                                                                                  s__state = 8560;
                                                                                } else {
                                                                                  goto _L___2;
                                                                                }
                                                                              } else {
                                                                                _L___2: 
                                                                                {
#line 395
                                                                                __cil_tmp61 = (ulong )s__s3__tmp__new_cipher__algorithms;
#line 395
                                                                                if (__cil_tmp61 + 256UL) {
#line 396
                                                                                  if (s__verify_mode + 2) {
                                                                                    goto _L___1;
                                                                                  } else {
#line 399
                                                                                    skip = 1;
#line 400
                                                                                    s__s3__tmp__cert_request = 0;
#line 401
                                                                                    s__state = 8560;
                                                                                  }
                                                                                } else {
                                                                                  _L___1: 
#line 405
                                                                                  s__s3__tmp__cert_request = 1;
#line 406
                                                                                  ret = nse_symbolic_int();
#line 407
                                                                                  if (ret <= 0) {
                                                                                    goto end;
                                                                                  }
#line 412
                                                                                  s__state = 8448;
#line 413
                                                                                  s__s3__tmp__next_state___0 = 8576;
#line 414
                                                                                  s__init_num = 0;
                                                                                }
                                                                                }
                                                                              }
                                                                            } else {
#line 418
                                                                              skip = 1;
#line 419
                                                                              s__s3__tmp__cert_request = 0;
#line 420
                                                                              s__state = 8560;
                                                                            }
                                                                            goto switch_1_break;
                                                                            switch_1_8560: ;
                                                                            switch_1_8561: 
#line 425
                                                                            ret = nse_symbolic_int();
#line 426
                                                                            if (ret <= 0) {
                                                                              goto end;
                                                                            }
#line 431
                                                                            s__s3__tmp__next_state___0 = 8576;
#line 432
                                                                            s__state = 8448;
#line 433
                                                                            s__init_num = 0;
                                                                            goto switch_1_break;
                                                                            switch_1_8448: 
#line 436
                                                                            if (num1 > 0L) {
#line 437
                                                                              s__rwstate = 2;
#line 438
                                                                              num1 = tmp___8;
#line 439
                                                                              if (num1 <= 0L) {
#line 440
                                                                                ret = -1;
                                                                                goto end;
                                                                              }
#line 445
                                                                              s__rwstate = 1;
                                                                            }
#line 449
                                                                            s__state = s__s3__tmp__next_state___0;
                                                                            goto switch_1_break;
                                                                            switch_1_8576: ;
                                                                            switch_1_8577: 
#line 453
                                                                            ret = nse_symbolic_int();
#line 454
                                                                            if (ret <= 0) {
                                                                              goto end;
                                                                            }
#line 459
                                                                            if (ret == 2) {
#line 460
                                                                              s__state = 8466;
                                                                            } else {
#line 462
                                                                              ret = nse_symbolic_int();
#line 463
                                                                              if (ret <= 0) {
                                                                                goto end;
                                                                              }
#line 468
                                                                              s__init_num = 0;
#line 469
                                                                              s__state = 8592;
                                                                            }
                                                                            goto switch_1_break;
                                                                            switch_1_8592: ;
                                                                            switch_1_8593: 
#line 474
                                                                            ret = nse_symbolic_int();
#line 475
                                                                            if (ret <= 0) {
                                                                              goto end;
                                                                            }
#line 480
                                                                            s__state = 8608;
#line 481
                                                                            s__init_num = 0;
                                                                            goto switch_1_break;
                                                                            switch_1_8608: ;
                                                                            switch_1_8609: 
#line 485
                                                                            ret = nse_symbolic_int();
#line 486
                                                                            if (ret <= 0) {
                                                                              goto end;
                                                                            }
#line 491
                                                                            s__state = 8640;
#line 492
                                                                            s__init_num = 0;
                                                                            goto switch_1_break;
                                                                            switch_1_8640: ;
                                                                            switch_1_8641: 
#line 496
                                                                            ret = nse_symbolic_int();
#line 497
                                                                            if (ret <= 0) {
                                                                              goto end;
                                                                            }
#line 502
                                                                            if (s__hit) {
#line 503
                                                                              s__state = 3;
                                                                            } else {
#line 505
                                                                              s__state = 8656;
                                                                            }
#line 507
                                                                            s__init_num = 0;
                                                                            goto switch_1_break;
                                                                            switch_1_8656: ;
                                                                            switch_1_8657: 
#line 511
                                                                            s__session__cipher = s__s3__tmp__new_cipher;
#line 512
                                                                            if (! tmp___9) {
#line 513
                                                                              ret = -1;
                                                                              goto end;
                                                                            }
#line 518
                                                                            ret = nse_symbolic_int();
#line 519
                                                                            if (blastFlag == 2) {
#line 520
                                                                              blastFlag = 3;
                                                                            }
#line 524
                                                                            if (ret <= 0) {
                                                                              goto end;
                                                                            }
#line 529
                                                                            s__state = 8672;
#line 530
                                                                            s__init_num = 0;
#line 531
                                                                            if (! tmp___10) {
#line 532
                                                                              ret = -1;
                                                                              goto end;
                                                                            }
                                                                            goto switch_1_break;
                                                                            switch_1_8672: ;
                                                                            switch_1_8673: 
#line 540
                                                                            ret = nse_symbolic_int();
#line 541
                                                                            nse_assert(blastFlag != 3);
#line 546
                                                                            if (ret <= 0) {
                                                                              goto end;
                                                                            }
#line 551
                                                                            s__state = 8448;
#line 552
                                                                            if (s__hit) {
#line 553
                                                                              s__s3__tmp__next_state___0 = 8640;
                                                                            } else {
#line 555
                                                                              s__s3__tmp__next_state___0 = 3;
                                                                            }
#line 557
                                                                            s__init_num = 0;
                                                                            goto switch_1_break;
                                                                            switch_1_3: 
#line 560
                                                                            s__init_buf___0 = 0;
#line 561
                                                                            s__init_num = 0;
#line 562
                                                                            if (got_new_session) {
#line 563
                                                                              s__new_session = 0;
#line 564
                                                                              s__ctx__stats__sess_accept_good ++;
#line 565
                                                                              if (cb != 0) {

                                                                              }
                                                                            }
#line 573
                                                                            ret = 1;
                                                                            goto end;
                                                                            switch_1_default: 
#line 576
                                                                            ret = -1;
                                                                            goto end;
                                                                          } else {
                                                                            switch_1_break: ;
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
                    }
                  }
                }
              }
            }
          }
        }
      }
    }
#line 617
    if (! s__s3__tmp__reuse_message) {
#line 618
      if (! skip) {
#line 619
        if (s__debug) {
#line 620
          ret = nse_symbolic_int();
#line 621
          if (ret <= 0) {
            goto end;
          }
        }
#line 629
        if (cb != 0) {
#line 630
          if (s__state != state) {
#line 631
            new_state = s__state;
#line 632
            s__state = state;
#line 633
            s__state = new_state;
          }
        }
      }
    }
#line 646
    skip = 0;
  }
  while_0_break: /* CIL Label */ ;
  }

  end: 
#line 651
  s__in_handshake --;
#line 652
  if (cb != 0) {

  }
#line 657
  return (ret);
}
}
#line 662 "s3_srvr_2_BUG.cil.c"
int main() 
{ int s ;
  int tmp ;

  {
  {
#line 668
  s = 8464;
#line 669
  tmp = ssl3_accept(s);
  }
#line 671
  return 0;
}
}
