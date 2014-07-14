typedef unsigned long ulong;

int nse_symbolic_int();
ulong nse_symbolic_ulong();
long nse_symbolic_long();
void nse_assert(bool);

#line 4 "s3_srvr_1.cil.c"
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
  int buf = nse_symbolic_int() ;
  ulong l ;
  ulong Time ;
  ulong tmp = nse_symbolic_ulong() ;
  int cb ;
  long num1 ;
  int ret ;
  int new_state ;
  int state ;
  int skip ;
  int got_new_session ;
  int tmp___1 = nse_symbolic_int() ;
  int tmp___2 = nse_symbolic_int() ;
  int tmp___3 ;
  int tmp___4 ;
  int tmp___5 ;
  int tmp___6 ;
  int tmp___7 ;
  long tmp___8 = nse_symbolic_long() ;
  int tmp___9 ;
  int tmp___10 ;
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
  Time = tmp;
#line 63
  cb = 0;
#line 64
  ret = -1;
#line 65
  skip = 0;
#line 66
  got_new_session = 0;
#line 67
  if (s__info_callback != 0) {
#line 68
    cb = s__info_callback;
  } else {
#line 70
    if (s__ctx__info_callback != 0) {
#line 71
      cb = s__ctx__info_callback;
    }
  }
#line 76
  s__in_handshake ++;
#line 77
  if (tmp___1 + 12288) {
#line 78
    if (tmp___2 + 16384) {

    }
  }
#line 86
  if (s__cert == 0) {
#line 87
    return (-1);
  }
  {
#line 92
  for (int i = 0; i < 12; ++i) {
    while_0_continue: /* CIL Label */ ;
#line 94
    state = s__state;
#line 95
    if (s__state == 12292) {
      goto switch_1_12292;
    } else {
#line 98
      if (s__state == 16384) {
        goto switch_1_16384;
      } else {
#line 101
        if (s__state == 8192) {
          goto switch_1_8192;
        } else {
#line 104
          if (s__state == 24576) {
            goto switch_1_24576;
          } else {
#line 107
            if (s__state == 8195) {
              goto switch_1_8195;
            } else {
#line 110
              if (s__state == 8480) {
                goto switch_1_8480;
              } else {
#line 113
                if (s__state == 8481) {
                  goto switch_1_8481;
                } else {
#line 116
                  if (s__state == 8482) {
                    goto switch_1_8482;
                  } else {
#line 119
                    if (s__state == 8464) {
                      goto switch_1_8464;
                    } else {
#line 122
                      if (s__state == 8465) {
                        goto switch_1_8465;
                      } else {
#line 125
                        if (s__state == 8466) {
                          goto switch_1_8466;
                        } else {
#line 128
                          if (s__state == 8496) {
                            goto switch_1_8496;
                          } else {
#line 131
                            if (s__state == 8497) {
                              goto switch_1_8497;
                            } else {
#line 134
                              if (s__state == 8512) {
                                goto switch_1_8512;
                              } else {
#line 137
                                if (s__state == 8513) {
                                  goto switch_1_8513;
                                } else {
#line 140
                                  if (s__state == 8528) {
                                    goto switch_1_8528;
                                  } else {
#line 143
                                    if (s__state == 8529) {
                                      goto switch_1_8529;
                                    } else {
#line 146
                                      if (s__state == 8544) {
                                        goto switch_1_8544;
                                      } else {
#line 149
                                        if (s__state == 8545) {
                                          goto switch_1_8545;
                                        } else {
#line 152
                                          if (s__state == 8560) {
                                            goto switch_1_8560;
                                          } else {
#line 155
                                            if (s__state == 8561) {
                                              goto switch_1_8561;
                                            } else {
#line 158
                                              if (s__state == 8448) {
                                                goto switch_1_8448;
                                              } else {
#line 161
                                                if (s__state == 8576) {
                                                  goto switch_1_8576;
                                                } else {
#line 164
                                                  if (s__state == 8577) {
                                                    goto switch_1_8577;
                                                  } else {
#line 167
                                                    if (s__state == 8592) {
                                                      goto switch_1_8592;
                                                    } else {
#line 170
                                                      if (s__state == 8593) {
                                                        goto switch_1_8593;
                                                      } else {
#line 173
                                                        if (s__state == 8608) {
                                                          goto switch_1_8608;
                                                        } else {
#line 176
                                                          if (s__state == 8609) {
                                                            goto switch_1_8609;
                                                          } else {
#line 179
                                                            if (s__state == 8640) {
                                                              goto switch_1_8640;
                                                            } else {
#line 182
                                                              if (s__state == 8641) {
                                                                goto switch_1_8641;
                                                              } else {
#line 185
                                                                if (s__state == 8656) {
                                                                  goto switch_1_8656;
                                                                } else {
#line 188
                                                                  if (s__state == 8657) {
                                                                    goto switch_1_8657;
                                                                  } else {
#line 191
                                                                    if (s__state == 8672) {
                                                                      goto switch_1_8672;
                                                                    } else {
#line 194
                                                                      if (s__state == 8673) {
                                                                        goto switch_1_8673;
                                                                      } else {
#line 197
                                                                        if (s__state == 3) {
                                                                          goto switch_1_3;
                                                                        } else {
                                                                          goto switch_1_default;
#line 202
                                                                          if (0) {
                                                                            switch_1_12292: 
#line 204
                                                                            s__new_session = 1;
                                                                            switch_1_16384: ;
                                                                            switch_1_8192: ;
                                                                            switch_1_24576: ;
                                                                            switch_1_8195: 
#line 209
                                                                            s__server = 1;
#line 210
                                                                            if (cb != 0) {

                                                                            }
                                                                            {
#line 215
                                                                            __cil_tmp55 = s__version * 8;
#line 215
                                                                            if (__cil_tmp55 != 3) {
#line 216
                                                                              return (-1);
                                                                            }
                                                                            }
#line 220
                                                                            s__type = 8192;
#line 221
                                                                            if (s__init_buf___0 == 0) {
#line 222
                                                                              tmp___3 = nse_symbolic_int();
#line 223
                                                                              if (! tmp___3) {
#line 224
                                                                                ret = -1;
                                                                                goto end;
                                                                              }
#line 229
                                                                              s__init_buf___0 = buf;
                                                                            }
#line 233
                                                                            tmp___4 = nse_symbolic_int();
#line 234
                                                                            if (! tmp___4) {
#line 235
                                                                              ret = -1;
                                                                              goto end;
                                                                            }
#line 240
                                                                            s__init_num = 0;
#line 241
                                                                            if (s__state != 12292) {
#line 242
                                                                              tmp___5 = nse_symbolic_int();
#line 243
                                                                              if (! tmp___5) {
#line 244
                                                                                ret = -1;
                                                                                goto end;
                                                                              }
#line 249
                                                                              s__state = 8464;
#line 250
                                                                              s__ctx__stats__sess_accept ++;
                                                                            } else {
#line 252
                                                                              s__ctx__stats__sess_accept_renegotiate ++;
#line 253
                                                                              s__state = 8480;
                                                                            }
                                                                            goto switch_1_break;
                                                                            switch_1_8480: ;
                                                                            switch_1_8481: 
#line 258
                                                                            s__shutdown = 0;
#line 259
                                                                            ret = nse_symbolic_int();
#line 260
                                                                            if (ret <= 0) {
                                                                              goto end;
                                                                            }
#line 265
                                                                            s__s3__tmp__next_state___0 = 8482;
#line 266
                                                                            s__state = 8448;
#line 267
                                                                            s__init_num = 0;
                                                                            goto switch_1_break;
                                                                            switch_1_8482: 
#line 270
                                                                            s__state = 3;
                                                                            goto switch_1_break;
                                                                            switch_1_8464: ;
                                                                            switch_1_8465: ;
                                                                            switch_1_8466: 
#line 275
                                                                            s__shutdown = 0;
#line 276
                                                                            ret = nse_symbolic_int();
#line 277
                                                                            if (blastFlag == 0) {
#line 278
                                                                              blastFlag = 1;
                                                                            }
#line 282
                                                                            if (ret <= 0) {
                                                                              goto end;
                                                                            }
#line 287
                                                                            got_new_session = 1;
#line 288
                                                                            s__state = 8496;
#line 289
                                                                            s__init_num = 0;
                                                                            goto switch_1_break;
                                                                            switch_1_8496: ;
                                                                            switch_1_8497: 
#line 293
                                                                            ret = nse_symbolic_int();
#line 294
                                                                            if (blastFlag == 1) {
#line 295
                                                                              blastFlag = 2;
                                                                            }
#line 299
                                                                            if (ret <= 0) {
                                                                              goto end;
                                                                            }
#line 304
                                                                            if (s__hit) {
#line 305
                                                                              s__state = 8656;
                                                                            } else {
#line 307
                                                                              s__state = 8512;
                                                                            }
#line 309
                                                                            s__init_num = 0;
                                                                            goto switch_1_break;
                                                                            switch_1_8512: ;
                                                                            switch_1_8513: ;
                                                                            {
#line 313
                                                                            __cil_tmp56 = (ulong )s__s3__tmp__new_cipher__algorithms;
#line 313
                                                                            if (__cil_tmp56 + 256UL) {
#line 314
                                                                              skip = 1;
                                                                            } else {
#line 316
                                                                              ret = nse_symbolic_int();
#line 317
                                                                              if (ret <= 0) {
                                                                                goto end;
                                                                              }
                                                                            }
                                                                            }
#line 323
                                                                            s__state = 8528;
#line 324
                                                                            s__init_num = 0;
                                                                            goto switch_1_break;
                                                                            switch_1_8528: ;
                                                                            switch_1_8529: 
#line 328
                                                                            l = (ulong )s__s3__tmp__new_cipher__algorithms;
                                                                            {
#line 329
                                                                            __cil_tmp57 = (ulong )s__options;
#line 329
                                                                            if (__cil_tmp57 + 2097152UL) {
#line 330
                                                                              s__s3__tmp__use_rsa_tmp = 1;
                                                                            } else {
#line 332
                                                                              s__s3__tmp__use_rsa_tmp = 0;
                                                                            }
                                                                            }
#line 334
                                                                            if (s__s3__tmp__use_rsa_tmp) {
                                                                              goto _L___0;
                                                                            } else {
#line 337
                                                                              if (l + 30UL) {
                                                                                goto _L___0;
                                                                              } else {
#line 340
                                                                                if (l + 1UL) {
#line 341
                                                                                  if (s__cert__pkeys__AT0__privatekey == 0) {
                                                                                    goto _L___0;
                                                                                  } else {
                                                                                    {
#line 344
                                                                                    __cil_tmp58 = (ulong )s__s3__tmp__new_cipher__algo_strength;
#line 344
                                                                                    if (__cil_tmp58 + 2UL) {
#line 345
                                                                                      tmp___6 = nse_symbolic_int();
                                                                                      {
#line 346
                                                                                      __cil_tmp59 = (ulong )s__s3__tmp__new_cipher__algo_strength;
#line 346
                                                                                      if (__cil_tmp59 + 4UL) {
#line 347
                                                                                        tmp___7 = 512;
                                                                                      } else {
#line 349
                                                                                        tmp___7 = 1024;
                                                                                      }
                                                                                      }
                                                                                      {
#line 351
                                                                                      __cil_tmp60 = tmp___6 * 8;
#line 351
                                                                                      if (__cil_tmp60 > tmp___7) {
                                                                                        _L___0: 
#line 353
                                                                                        ret = nse_symbolic_int();
#line 354
                                                                                        if (ret <= 0) {
                                                                                          goto end;
                                                                                        }
                                                                                      } else {
#line 360
                                                                                        skip = 1;
                                                                                      }
                                                                                      }
                                                                                    } else {
#line 363
                                                                                      skip = 1;
                                                                                    }
                                                                                    }
                                                                                  }
                                                                                } else {
#line 367
                                                                                  skip = 1;
                                                                                }
                                                                              }
                                                                            }
#line 371
                                                                            s__state = 8544;
#line 372
                                                                            s__init_num = 0;
                                                                            goto switch_1_break;
                                                                            switch_1_8544: ;
                                                                            switch_1_8545: ;
#line 376
                                                                            if (s__verify_mode + 1) {
#line 377
                                                                              if (s__session__peer != 0) {
#line 378
                                                                                if (s__verify_mode + 4) {
#line 379
                                                                                  skip = 1;
#line 380
                                                                                  s__s3__tmp__cert_request = 0;
#line 381
                                                                                  s__state = 8560;
                                                                                } else {
                                                                                  goto _L___2;
                                                                                }
                                                                              } else {
                                                                                _L___2: 
                                                                                {
#line 387
                                                                                __cil_tmp61 = (ulong )s__s3__tmp__new_cipher__algorithms;
#line 387
                                                                                if (__cil_tmp61 + 256UL) {
#line 388
                                                                                  if (s__verify_mode + 2) {
                                                                                    goto _L___1;
                                                                                  } else {
#line 391
                                                                                    skip = 1;
#line 392
                                                                                    s__s3__tmp__cert_request = 0;
#line 393
                                                                                    s__state = 8560;
                                                                                  }
                                                                                } else {
                                                                                  _L___1: 
#line 397
                                                                                  s__s3__tmp__cert_request = 1;
#line 398
                                                                                  ret = nse_symbolic_int();
#line 399
                                                                                  if (ret <= 0) {
                                                                                    goto end;
                                                                                  }
#line 404
                                                                                  s__state = 8448;
#line 405
                                                                                  s__s3__tmp__next_state___0 = 8576;
#line 406
                                                                                  s__init_num = 0;
                                                                                }
                                                                                }
                                                                              }
                                                                            } else {
#line 410
                                                                              skip = 1;
#line 411
                                                                              s__s3__tmp__cert_request = 0;
#line 412
                                                                              s__state = 8560;
                                                                            }
                                                                            goto switch_1_break;
                                                                            switch_1_8560: ;
                                                                            switch_1_8561: 
#line 417
                                                                            ret = nse_symbolic_int();
#line 418
                                                                            if (ret <= 0) {
                                                                              goto end;
                                                                            }
#line 423
                                                                            s__s3__tmp__next_state___0 = 8576;
#line 424
                                                                            s__state = 8448;
#line 425
                                                                            s__init_num = 0;
                                                                            goto switch_1_break;
                                                                            switch_1_8448: 
#line 428
                                                                            num1 = nse_symbolic_long();
#line 429
                                                                            if (num1 > 0L) {
#line 430
                                                                              s__rwstate = 2;
#line 431
                                                                              num1 = tmp___8;
#line 432
                                                                              if (num1 <= 0L) {
#line 433
                                                                                ret = -1;
                                                                                goto end;
                                                                              }
#line 438
                                                                              s__rwstate = 1;
                                                                            }
#line 442
                                                                            s__state = s__s3__tmp__next_state___0;
                                                                            goto switch_1_break;
                                                                            switch_1_8576: ;
                                                                            switch_1_8577: 
#line 446
                                                                            ret = nse_symbolic_int();
#line 447
                                                                            if (ret <= 0) {
                                                                              goto end;
                                                                            }
#line 452
                                                                            if (ret == 2) {
#line 453
                                                                              s__state = 8466;
                                                                            } else {
#line 455
                                                                              ret = nse_symbolic_int();
#line 456
                                                                              if (ret <= 0) {
                                                                                goto end;
                                                                              }
#line 461
                                                                              s__init_num = 0;
#line 462
                                                                              s__state = 8592;
                                                                            }
                                                                            goto switch_1_break;
                                                                            switch_1_8592: ;
                                                                            switch_1_8593: 
#line 467
                                                                            ret = nse_symbolic_int();
#line 468
                                                                            if (ret <= 0) {
                                                                              goto end;
                                                                            }
#line 473
                                                                            s__state = 8608;
#line 474
                                                                            s__init_num = 0;
                                                                            goto switch_1_break;
                                                                            switch_1_8608: ;
                                                                            switch_1_8609: 
#line 478
                                                                            ret = nse_symbolic_int();
#line 479
                                                                            if (ret <= 0) {
                                                                              goto end;
                                                                            }
#line 484
                                                                            s__state = 8640;
#line 485
                                                                            s__init_num = 0;
                                                                            goto switch_1_break;
                                                                            switch_1_8640: ;
                                                                            switch_1_8641: 
#line 489
                                                                            ret = nse_symbolic_int();
#line 490
                                                                            if (blastFlag == 3) {
#line 491
                                                                              blastFlag = 4;
                                                                            }
#line 495
                                                                            if (ret <= 0) {
                                                                              goto end;
                                                                            }
#line 500
                                                                            if (s__hit) {
#line 501
                                                                              s__state = 3;
                                                                            } else {
#line 503
                                                                              s__state = 8656;
                                                                            }
#line 505
                                                                            s__init_num = 0;
                                                                            goto switch_1_break;
                                                                            switch_1_8656: ;
                                                                            switch_1_8657: 
#line 509
                                                                            s__session__cipher = s__s3__tmp__new_cipher;
#line 510
                                                                            tmp___9 = nse_symbolic_int();
#line 511
                                                                            if (! tmp___9) {
#line 512
                                                                              ret = -1;
                                                                              goto end;
                                                                            }
#line 517
                                                                            ret = nse_symbolic_int();
#line 518
                                                                            if (blastFlag == 2) {
#line 519
                                                                              blastFlag = 3;
                                                                            }
#line 523
                                                                            if (ret <= 0) {
                                                                              goto end;
                                                                            }
#line 528
                                                                            s__state = 8672;
#line 529
                                                                            s__init_num = 0;
#line 530
                                                                            tmp___10 = nse_symbolic_int();
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
                                                                            if (blastFlag == 4) {
#line 542
                                                                              blastFlag = 5;
                                                                            } else {
#line 544
                                                                              nse_assert(blastFlag != 5);
                                                                            }
#line 550
                                                                            if (ret <= 0) {
                                                                              goto end;
                                                                            }
#line 555
                                                                            s__state = 8448;
#line 556
                                                                            if (s__hit) {
#line 557
                                                                              s__s3__tmp__next_state___0 = 8640;
                                                                            } else {
#line 559
                                                                              s__s3__tmp__next_state___0 = 3;
                                                                            }
#line 561
                                                                            s__init_num = 0;
                                                                            goto switch_1_break;
                                                                            switch_1_3: 
#line 564
                                                                            s__init_buf___0 = 0;
#line 565
                                                                            s__init_num = 0;
#line 566
                                                                            if (got_new_session) {
#line 567
                                                                              s__new_session = 0;
#line 568
                                                                              s__ctx__stats__sess_accept_good ++;
#line 569
                                                                              if (cb != 0) {

                                                                              }
                                                                            }
#line 577
                                                                            ret = 1;
                                                                            goto end;
                                                                            switch_1_default: 
#line 580
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
#line 621
    if (! s__s3__tmp__reuse_message) {
#line 622
      if (! skip) {
#line 623
        if (s__debug) {
#line 624
          ret = nse_symbolic_int();
#line 625
          if (ret <= 0) {
            goto end;
          }
        }
#line 633
        if (cb != 0) {
#line 634
          if (s__state != state) {
#line 635
            new_state = s__state;
#line 636
            s__state = state;
#line 637
            s__state = new_state;
          }
        }
      }
    }
#line 650
    skip = 0;
  }
  while_0_break: /* CIL Label */ ;
  }

  end: 
#line 655
  s__in_handshake --;
#line 656
  if (cb != 0) {

  }
#line 661
  return (ret);
}
}

#line 666 "s3_srvr_1.cil.c"
int main() 
{ int s ;
  int tmp ;

  {
  {
#line 672
  s = 8464;
#line 673
  tmp = ssl3_accept(s);
  }
#line 675
  return 0;
}
}
