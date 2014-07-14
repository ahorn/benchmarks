typedef unsigned long ulong;

long nse_symbolic_long();
ulong nse_symbolic_ulong();
int nse_symbolic_int();

void nse_assert(bool);

#line 4 "s3_srvr_7.cil.c"
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
  for (int i = 0; i < 12; ++i) {
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
                                                                            }
#line 304
                                                                            if (ret <= 0) {
                                                                              goto end;
                                                                            }
#line 309
                                                                            if (s__hit) {
#line 310
                                                                              s__state = 8656;
                                                                            } else {
#line 312
                                                                              s__state = 8512;
                                                                            }
#line 314
                                                                            s__init_num = 0;
                                                                            goto switch_1_break;
                                                                            switch_1_8512: ;
                                                                            switch_1_8513: ;
                                                                            {
#line 318
                                                                            __cil_tmp56 = (ulong )s__s3__tmp__new_cipher__algorithms;
#line 318
                                                                            if (__cil_tmp56 + 256UL) {
#line 319
                                                                              skip = 1;
                                                                            } else {
#line 321
                                                                              ret = nse_symbolic_int();
#line 322
                                                                              if (blastFlag == 2) {
#line 323
                                                                                blastFlag = 6;
                                                                              }
#line 327
                                                                              if (ret <= 0) {
                                                                                goto end;
                                                                              }
                                                                            }
                                                                            }
#line 333
                                                                            s__state = 8528;
#line 334
                                                                            s__init_num = 0;
                                                                            goto switch_1_break;
                                                                            switch_1_8528: ;
                                                                            switch_1_8529: 
#line 338
                                                                            l = (ulong )s__s3__tmp__new_cipher__algorithms;
                                                                            {
#line 339
                                                                            __cil_tmp57 = (ulong )s__options;
#line 339
                                                                            if (__cil_tmp57 + 2097152UL) {
#line 340
                                                                              s__s3__tmp__use_rsa_tmp = 1;
                                                                            } else {
#line 342
                                                                              s__s3__tmp__use_rsa_tmp = 0;
                                                                            }
                                                                            }
#line 344
                                                                            if (s__s3__tmp__use_rsa_tmp) {
                                                                              goto _L___0;
                                                                            } else {
#line 347
                                                                              if (l + 30UL) {
                                                                                goto _L___0;
                                                                              } else {
#line 350
                                                                                if (l + 1UL) {
#line 351
                                                                                  if (s__cert__pkeys__AT0__privatekey == 0) {
                                                                                    goto _L___0;
                                                                                  } else {
                                                                                    {
#line 354
                                                                                    __cil_tmp58 = (ulong )s__s3__tmp__new_cipher__algo_strength;
#line 354
                                                                                    if (__cil_tmp58 + 2UL) {
                                                                                      {
#line 355
                                                                                      __cil_tmp59 = (ulong )s__s3__tmp__new_cipher__algo_strength;
#line 355
                                                                                      if (__cil_tmp59 + 4UL) {
#line 356
                                                                                        tmp___7 = 512;
                                                                                      } else {
#line 358
                                                                                        tmp___7 = 1024;
                                                                                      }
                                                                                      }
                                                                                      {
#line 360
                                                                                      __cil_tmp60 = tmp___6 * 8;
#line 360
                                                                                      if (__cil_tmp60 > tmp___7) {
                                                                                        _L___0: 
#line 362
                                                                                        ret = nse_symbolic_int();
#line 363
                                                                                        if (blastFlag == 6) {
#line 364
                                                                                          blastFlag = 7;
                                                                                        }
#line 368
                                                                                        if (ret <= 0) {
                                                                                          goto end;
                                                                                        }
                                                                                      } else {
#line 374
                                                                                        skip = 1;
                                                                                      }
                                                                                      }
                                                                                    } else {
#line 377
                                                                                      skip = 1;
                                                                                    }
                                                                                    }
                                                                                  }
                                                                                } else {
#line 381
                                                                                  skip = 1;
                                                                                }
                                                                              }
                                                                            }
#line 385
                                                                            s__state = 8544;
#line 386
                                                                            s__init_num = 0;
                                                                            goto switch_1_break;
                                                                            switch_1_8544: ;
                                                                            switch_1_8545: ;
#line 390
                                                                            if (s__verify_mode + 1) {
#line 391
                                                                              if (s__session__peer != 0) {
#line 392
                                                                                if (s__verify_mode + 4) {
#line 393
                                                                                  skip = 1;
#line 394
                                                                                  s__s3__tmp__cert_request = 0;
#line 395
                                                                                  s__state = 8560;
                                                                                } else {
                                                                                  goto _L___2;
                                                                                }
                                                                              } else {
                                                                                _L___2: 
                                                                                {
#line 401
                                                                                __cil_tmp61 = (ulong )s__s3__tmp__new_cipher__algorithms;
#line 401
                                                                                if (__cil_tmp61 + 256UL) {
#line 402
                                                                                  if (s__verify_mode + 2) {
                                                                                    goto _L___1;
                                                                                  } else {
#line 405
                                                                                    skip = 1;
#line 406
                                                                                    s__s3__tmp__cert_request = 0;
#line 407
                                                                                    s__state = 8560;
                                                                                  }
                                                                                } else {
                                                                                  _L___1: 
#line 411
                                                                                  s__s3__tmp__cert_request = 1;
#line 412
                                                                                  ret = nse_symbolic_int();
#line 413
                                                                                  nse_assert(blastFlag != 8);
#line 418
                                                                                  if (ret <= 0) {
                                                                                    goto end;
                                                                                  }
#line 423
                                                                                  s__state = 8448;
#line 424
                                                                                  s__s3__tmp__next_state___0 = 8576;
#line 425
                                                                                  s__init_num = 0;
                                                                                }
                                                                                }
                                                                              }
                                                                            } else {
#line 429
                                                                              skip = 1;
#line 430
                                                                              s__s3__tmp__cert_request = 0;
#line 431
                                                                              s__state = 8560;
                                                                            }
                                                                            goto switch_1_break;
                                                                            switch_1_8560: ;
                                                                            switch_1_8561: 
#line 436
                                                                            ret = nse_symbolic_int();
#line 437
                                                                            if (ret <= 0) {
                                                                              goto end;
                                                                            }
#line 442
                                                                            s__s3__tmp__next_state___0 = 8576;
#line 443
                                                                            s__state = 8448;
#line 444
                                                                            s__init_num = 0;
                                                                            goto switch_1_break;
                                                                            switch_1_8448: 
#line 447
                                                                            if (num1 > 0L) {
#line 448
                                                                              s__rwstate = 2;
#line 449
                                                                              num1 = tmp___8;
#line 450
                                                                              if (num1 <= 0L) {
#line 451
                                                                                ret = -1;
                                                                                goto end;
                                                                              }
#line 456
                                                                              s__rwstate = 1;
                                                                            }
#line 460
                                                                            s__state = s__s3__tmp__next_state___0;
                                                                            goto switch_1_break;
                                                                            switch_1_8576: ;
                                                                            switch_1_8577: 
#line 464
                                                                            ret = nse_symbolic_int();
#line 465
                                                                            if (ret <= 0) {
                                                                              goto end;
                                                                            }
#line 470
                                                                            if (ret == 2) {
#line 471
                                                                              s__state = 8466;
                                                                            } else {
#line 473
                                                                              ret = nse_symbolic_int();
#line 474
                                                                              if (ret <= 0) {
                                                                                goto end;
                                                                              }
#line 479
                                                                              s__init_num = 0;
#line 480
                                                                              s__state = 8592;
                                                                            }
                                                                            goto switch_1_break;
                                                                            switch_1_8592: ;
                                                                            switch_1_8593: 
#line 485
                                                                            ret = nse_symbolic_int();
#line 486
                                                                            if (ret <= 0) {
                                                                              goto end;
                                                                            }
#line 491
                                                                            s__state = 8608;
#line 492
                                                                            s__init_num = 0;
                                                                            goto switch_1_break;
                                                                            switch_1_8608: ;
                                                                            switch_1_8609: 
#line 496
                                                                            ret = nse_symbolic_int();
#line 497
                                                                            if (ret <= 0) {
                                                                              goto end;
                                                                            }
#line 502
                                                                            s__state = 8640;
#line 503
                                                                            s__init_num = 0;
                                                                            goto switch_1_break;
                                                                            switch_1_8640: ;
                                                                            switch_1_8641: 
#line 507
                                                                            ret = nse_symbolic_int();
#line 508
                                                                            nse_assert(blastFlag != 5);
#line 513
                                                                            if (ret <= 0) {
                                                                              goto end;
                                                                            }
#line 518
                                                                            if (s__hit) {
#line 519
                                                                              s__state = 3;
                                                                            } else {
#line 521
                                                                              s__state = 8656;
                                                                            }
#line 523
                                                                            s__init_num = 0;
                                                                            goto switch_1_break;
                                                                            switch_1_8656: ;
                                                                            switch_1_8657: 
#line 527
                                                                            s__session__cipher = s__s3__tmp__new_cipher;
#line 528
                                                                            if (! tmp___9) {
#line 529
                                                                              ret = -1;
                                                                              goto end;
                                                                            }
#line 534
                                                                            ret = nse_symbolic_int();
#line 535
                                                                            if (blastFlag == 2) {
#line 536
                                                                              blastFlag = 3;
                                                                            } else {
#line 538
                                                                              if (blastFlag == 4) {
#line 539
                                                                                blastFlag = 5;
                                                                              } else {
#line 541
                                                                                if (blastFlag == 7) {
#line 542
                                                                                  blastFlag = 8;
                                                                                }
                                                                              }
                                                                            }
#line 548
                                                                            if (ret <= 0) {
                                                                              goto end;
                                                                            }
#line 553
                                                                            s__state = 8672;
#line 554
                                                                            s__init_num = 0;
#line 555
                                                                            if (! tmp___10) {
#line 556
                                                                              ret = -1;
                                                                              goto end;
                                                                            }
                                                                            goto switch_1_break;
                                                                            switch_1_8672: ;
                                                                            switch_1_8673: 
#line 564
                                                                            ret = nse_symbolic_int();
#line 565
                                                                            if (blastFlag == 3) {
#line 566
                                                                              blastFlag = 4;
                                                                            }
#line 570
                                                                            if (ret <= 0) {
                                                                              goto end;
                                                                            }
#line 575
                                                                            s__state = 8448;
#line 576
                                                                            if (s__hit) {
#line 577
                                                                              s__s3__tmp__next_state___0 = 8640;
                                                                            } else {
#line 579
                                                                              s__s3__tmp__next_state___0 = 3;
                                                                            }
#line 581
                                                                            s__init_num = 0;
                                                                            goto switch_1_break;
                                                                            switch_1_3: 
#line 584
                                                                            s__init_buf___0 = 0;
#line 585
                                                                            s__init_num = 0;
#line 586
                                                                            if (got_new_session) {
#line 587
                                                                              s__new_session = 0;
#line 588
                                                                              s__ctx__stats__sess_accept_good ++;
#line 589
                                                                              if (cb != 0) {

                                                                              }
                                                                            }
#line 597
                                                                            ret = 1;
                                                                            goto end;
                                                                            switch_1_default: 
#line 600
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
#line 641
    if (! s__s3__tmp__reuse_message) {
#line 642
      if (! skip) {
#line 643
        if (s__debug) {
#line 644
          ret = nse_symbolic_int();
#line 645
          if (ret <= 0) {
            goto end;
          }
        }
#line 653
        if (cb != 0) {
#line 654
          if (s__state != state) {
#line 655
            new_state = s__state;
#line 656
            s__state = state;
#line 657
            s__state = new_state;
          }
        }
      }
    }
#line 670
    skip = 0;
  }
  while_0_break: /* CIL Label */ ;
  }

  end: 
#line 675
  s__in_handshake --;
#line 676
  if (cb != 0) {

  }
#line 681
  return (ret);
}
}
#line 686 "s3_srvr_7.cil.c"
int main() 
{ int s ;
  int tmp ;

  {
  {
#line 692
  s = 8464;
#line 693
  tmp = ssl3_accept(s);
  }
#line 695
  return 0;
}
}
