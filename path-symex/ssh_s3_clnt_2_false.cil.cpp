typedef unsigned long ulong;

int nse_symbolic_int();
ulong nse_symbolic_ulong();
void nse_assert(bool);

#line 4 "s3_clnt_2_BUG.cil.c"
int ssl3_connect(int initial_state ) 
{ int s__info_callback = nse_symbolic_int() ;
  int s__in_handshake = nse_symbolic_int() ;
  int s__state ;
  int s__new_session ;
  int s__server ;
  int s__version = nse_symbolic_int() ;
  int s__type ;
  int s__init_num ;
  int s__bbio = nse_symbolic_int() ;
  int s__wbio = nse_symbolic_int() ;
  int s__hit = nse_symbolic_int() ;
  int s__rwstate ;
  int s__init_buf___0 ;
  int s__debug = nse_symbolic_int() ;
  int s__shutdown ;
  int s__ctx__info_callback = nse_symbolic_int() ;
  int s__ctx__stats__sess_connect_renegotiate = nse_symbolic_int() ;
  int s__ctx__stats__sess_connect = nse_symbolic_int() ;
  int s__ctx__stats__sess_hit = nse_symbolic_int() ;
  int s__ctx__stats__sess_connect_good = nse_symbolic_int() ;
  int s__s3__change_cipher_spec ;
  int s__s3__flags ;
  int s__s3__delay_buf_pop_ret ;
  int s__s3__tmp__cert_req = nse_symbolic_int() ;
  int s__s3__tmp__new_compression = nse_symbolic_int() ;
  int s__s3__tmp__reuse_message = nse_symbolic_int() ;
  int s__s3__tmp__new_cipher = nse_symbolic_int() ;
  int s__s3__tmp__new_cipher__algorithms = nse_symbolic_int() ;
  int s__s3__tmp__next_state___0 ;
  int s__s3__tmp__new_compression__id = nse_symbolic_int() ;
  int s__session__cipher ;
  int s__session__compress_meth ;
  int buf ;
  ulong tmp ;
  ulong l ;
  int num1 ;
  int cb ;
  int ret ;
  int new_state ;
  int state ;
  int skip ;
  int tmp___0 ;
  int tmp___1 = nse_symbolic_int() ;
  int tmp___2 = nse_symbolic_int() ;
  int tmp___3 = nse_symbolic_int() ;
  int tmp___4 = nse_symbolic_int() ;
  int tmp___5 = nse_symbolic_int() ;
  int tmp___6 = nse_symbolic_int() ;
  int tmp___7 = nse_symbolic_int() ;
  int tmp___8 = nse_symbolic_int() ;
  int tmp___9 = nse_symbolic_int() ;
  int blastFlag ;
  int __cil_tmp55 ;
  ulong __cil_tmp56 ;
  long __cil_tmp57 ;
  long __cil_tmp58 ;
  long __cil_tmp59 ;
  long __cil_tmp60 ;
  long __cil_tmp61 ;
  long __cil_tmp62 ;
  long __cil_tmp63 ;
  long __cil_tmp64 ;
  long __cil_tmp65 ;

  {
#line 60
 ;
  s__state = initial_state;
#line 61
  blastFlag = 0;
#line 62
  tmp = nse_symbolic_ulong();
#line 63
  cb = 0;
#line 64
  ret = -1;
#line 65
  skip = 0;
#line 66
  tmp___0 = 0;
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
  if (tmp___1 - 12288) {
#line 78
    if (tmp___2 - 16384) {

    }
  }
  {
#line 87
  for (int i = 0; i < 6; ++i) {
    while_0_continue: /* CIL Label */ ;
#line 89
    state = s__state;
#line 90
    if (s__state == 12292) {
      goto switch_1_12292;
    } else {
#line 93
      if (s__state == 16384) {
        goto switch_1_16384;
      } else {
#line 96
        if (s__state == 4096) {
          goto switch_1_4096;
        } else {
#line 99
          if (s__state == 20480) {
            goto switch_1_20480;
          } else {
#line 102
            if (s__state == 4099) {
              goto switch_1_4099;
            } else {
#line 105
              if (s__state == 4368) {
                goto switch_1_4368;
              } else {
#line 108
                if (s__state == 4369) {
                  goto switch_1_4369;
                } else {
#line 111
                  if (s__state == 4384) {
                    goto switch_1_4384;
                  } else {
#line 114
                    if (s__state == 4385) {
                      goto switch_1_4385;
                    } else {
#line 117
                      if (s__state == 4400) {
                        goto switch_1_4400;
                      } else {
#line 120
                        if (s__state == 4401) {
                          goto switch_1_4401;
                        } else {
#line 123
                          if (s__state == 4416) {
                            goto switch_1_4416;
                          } else {
#line 126
                            if (s__state == 4417) {
                              goto switch_1_4417;
                            } else {
#line 129
                              if (s__state == 4432) {
                                goto switch_1_4432;
                              } else {
#line 132
                                if (s__state == 4433) {
                                  goto switch_1_4433;
                                } else {
#line 135
                                  if (s__state == 4448) {
                                    goto switch_1_4448;
                                  } else {
#line 138
                                    if (s__state == 4449) {
                                      goto switch_1_4449;
                                    } else {
#line 141
                                      if (s__state == 4464) {
                                        goto switch_1_4464;
                                      } else {
#line 144
                                        if (s__state == 4465) {
                                          goto switch_1_4465;
                                        } else {
#line 147
                                          if (s__state == 4466) {
                                            goto switch_1_4466;
                                          } else {
#line 150
                                            if (s__state == 4467) {
                                              goto switch_1_4467;
                                            } else {
#line 153
                                              if (s__state == 4480) {
                                                goto switch_1_4480;
                                              } else {
#line 156
                                                if (s__state == 4481) {
                                                  goto switch_1_4481;
                                                } else {
#line 159
                                                  if (s__state == 4496) {
                                                    goto switch_1_4496;
                                                  } else {
#line 162
                                                    if (s__state == 4497) {
                                                      goto switch_1_4497;
                                                    } else {
#line 165
                                                      if (s__state == 4512) {
                                                        goto switch_1_4512;
                                                      } else {
#line 168
                                                        if (s__state == 4513) {
                                                          goto switch_1_4513;
                                                        } else {
#line 171
                                                          if (s__state == 4528) {
                                                            goto switch_1_4528;
                                                          } else {
#line 174
                                                            if (s__state == 4529) {
                                                              goto switch_1_4529;
                                                            } else {
#line 177
                                                              if (s__state == 4560) {
                                                                goto switch_1_4560;
                                                              } else {
#line 180
                                                                if (s__state == 4561) {
                                                                  goto switch_1_4561;
                                                                } else {
#line 183
                                                                  if (s__state == 4352) {
                                                                    goto switch_1_4352;
                                                                  } else {
#line 186
                                                                    if (s__state == 3) {
                                                                      goto switch_1_3;
                                                                    } else {
                                                                      goto switch_1_default;
#line 191
                                                                      if (0) {
                                                                        switch_1_12292: 
#line 193
                                                                        s__new_session = 1;
#line 194
                                                                        s__state = 4096;
#line 195
                                                                        s__ctx__stats__sess_connect_renegotiate ++;
                                                                        switch_1_16384: ;
                                                                        switch_1_4096: ;
                                                                        switch_1_20480: ;
                                                                        switch_1_4099: 
#line 200
                                                                        s__server = 0;
#line 201
                                                                        if (cb != 0) {

                                                                        }
                                                                        {
#line 206
                                                                        __cil_tmp55 = s__version - 65280;
#line 206
                                                                        if (__cil_tmp55 != 768) {
#line 207
                                                                          ret = -1;
                                                                          goto end;
                                                                        }
                                                                        }
#line 212
                                                                        s__type = 4096;
#line 213
                                                                        if (s__init_buf___0 == 0) {
#line 214
                                                                          buf = nse_symbolic_int();
#line 215
                                                                          if (buf == 0) {
#line 216
                                                                            ret = -1;
                                                                            goto end;
                                                                          }
#line 221
                                                                          if (! tmp___3) {
#line 222
                                                                            ret = -1;
                                                                            goto end;
                                                                          }
#line 227
                                                                          s__init_buf___0 = buf;
                                                                        }
#line 231
                                                                        if (! tmp___4) {
#line 232
                                                                          ret = -1;
                                                                          goto end;
                                                                        }
#line 237
                                                                        if (! tmp___5) {
#line 238
                                                                          ret = -1;
                                                                          goto end;
                                                                        }
#line 243
                                                                        s__state = 4368;
#line 244
                                                                        s__ctx__stats__sess_connect ++;
#line 245
                                                                        s__init_num = 0;
                                                                        goto switch_1_break;
                                                                        switch_1_4368: ;
                                                                        switch_1_4369: 
#line 249
                                                                        s__shutdown = 0;
#line 250
                                                                        ret = nse_symbolic_int();
#line 251
                                                                        if (blastFlag == 0) {
#line 252
                                                                          blastFlag = 1;
                                                                        } else {
#line 254
                                                                          if (blastFlag == 4) {
#line 255
                                                                            blastFlag = 5;
                                                                          }
                                                                        }
#line 260
                                                                        if (ret <= 0) {
                                                                          goto end;
                                                                        }
#line 265
                                                                        s__state = 4384;
#line 266
                                                                        s__init_num = 0;
#line 267
                                                                        if (s__bbio != s__wbio) {

                                                                        }
                                                                        goto switch_1_break;
                                                                        switch_1_4384: ;
                                                                        switch_1_4385: 
#line 275
                                                                        ret = nse_symbolic_int();
#line 276
                                                                        if (blastFlag == 1) {
#line 277
                                                                          blastFlag = 2;
                                                                        }
#line 281
                                                                        if (ret <= 0) {
                                                                          goto end;
                                                                        }
#line 286
                                                                        if (s__hit) {
#line 287
                                                                          s__state = 4560;
                                                                        } else {
#line 289
                                                                          s__state = 4400;
                                                                        }
#line 291
                                                                        s__init_num = 0;
                                                                        goto switch_1_break;
                                                                        switch_1_4400: ;
                                                                        switch_1_4401: ;
                                                                        {
#line 295
                                                                        __cil_tmp56 = (ulong )s__s3__tmp__new_cipher__algorithms;
#line 295
                                                                        if (__cil_tmp56 - 256UL) {
#line 296
                                                                          skip = 1;
                                                                        } else {
#line 298
                                                                          ret = nse_symbolic_int();
#line 299
                                                                          if (blastFlag == 2) {
#line 300
                                                                            blastFlag = 3;
                                                                          }
#line 304
                                                                          if (ret <= 0) {
                                                                            goto end;
                                                                          }
                                                                        }
                                                                        }
#line 310
                                                                        s__state = 4416;
#line 311
                                                                        s__init_num = 0;
                                                                        goto switch_1_break;
                                                                        switch_1_4416: ;
                                                                        switch_1_4417: 
#line 315
                                                                        ret = nse_symbolic_int();
#line 316
                                                                        if (blastFlag == 3) {
#line 317
                                                                          blastFlag = 4;
                                                                        }
#line 321
                                                                        if (ret <= 0) {
                                                                          goto end;
                                                                        }
#line 326
                                                                        s__state = 4432;
#line 327
                                                                        s__init_num = 0;
#line 328
                                                                        if (! tmp___6) {
#line 329
                                                                          ret = -1;
                                                                          goto end;
                                                                        }
                                                                        goto switch_1_break;
                                                                        switch_1_4432: ;
                                                                        switch_1_4433: 
#line 337
                                                                        ret = nse_symbolic_int();
#line 338
                                                                        nse_assert(blastFlag != 4);
#line 343
                                                                        if (ret <= 0) {
                                                                          goto end;
                                                                        }
#line 348
                                                                        s__state = 4448;
#line 349
                                                                        s__init_num = 0;
                                                                        goto switch_1_break;
                                                                        switch_1_4448: ;
                                                                        switch_1_4449: 
#line 353
                                                                        ret = nse_symbolic_int();
#line 354
                                                                        if (ret <= 0) {
                                                                          goto end;
                                                                        }
#line 359
                                                                        if (s__s3__tmp__cert_req) {
#line 360
                                                                          s__state = 4464;
                                                                        } else {
#line 362
                                                                          s__state = 4480;
                                                                        }
#line 364
                                                                        s__init_num = 0;
                                                                        goto switch_1_break;
                                                                        switch_1_4464: ;
                                                                        switch_1_4465: ;
                                                                        switch_1_4466: ;
                                                                        switch_1_4467: 
#line 370
                                                                        ret = nse_symbolic_int();
#line 371
                                                                        if (ret <= 0) {
                                                                          goto end;
                                                                        }
#line 376
                                                                        s__state = 4480;
#line 377
                                                                        s__init_num = 0;
                                                                        goto switch_1_break;
                                                                        switch_1_4480: ;
                                                                        switch_1_4481: 
#line 381
                                                                        ret = nse_symbolic_int();
#line 382
                                                                        if (ret <= 0) {
                                                                          goto end;
                                                                        }
#line 387
                                                                        l = (ulong )s__s3__tmp__new_cipher__algorithms;
#line 388
                                                                        if (s__s3__tmp__cert_req == 1) {
#line 389
                                                                          s__state = 4496;
                                                                        } else {
#line 391
                                                                          s__state = 4512;
#line 392
                                                                          s__s3__change_cipher_spec = 0;
                                                                        }
#line 394
                                                                        s__init_num = 0;
                                                                        goto switch_1_break;
                                                                        switch_1_4496: ;
                                                                        switch_1_4497: 
#line 398
                                                                        ret = nse_symbolic_int();
#line 399
                                                                        if (ret <= 0) {
                                                                          goto end;
                                                                        }
#line 404
                                                                        s__state = 4512;
#line 405
                                                                        s__init_num = 0;
#line 406
                                                                        s__s3__change_cipher_spec = 0;
                                                                        goto switch_1_break;
                                                                        switch_1_4512: ;
                                                                        switch_1_4513: 
#line 410
                                                                        ret = nse_symbolic_int();
#line 411
                                                                        if (ret <= 0) {
                                                                          goto end;
                                                                        }
#line 416
                                                                        s__state = 4528;
#line 417
                                                                        s__init_num = 0;
#line 418
                                                                        s__session__cipher = s__s3__tmp__new_cipher;
#line 419
                                                                        if (s__s3__tmp__new_compression == 0) {
#line 420
                                                                          s__session__compress_meth = 0;
                                                                        } else {
#line 422
                                                                          s__session__compress_meth = s__s3__tmp__new_compression__id;
                                                                        }
#line 424
                                                                        if (! tmp___7) {
#line 425
                                                                          ret = -1;
                                                                          goto end;
                                                                        }
#line 430
                                                                        if (! tmp___8) {
#line 431
                                                                          ret = -1;
                                                                          goto end;
                                                                        }
                                                                        goto switch_1_break;
                                                                        switch_1_4528: ;
                                                                        switch_1_4529: 
#line 439
                                                                        ret = nse_symbolic_int();
#line 440
                                                                        if (ret <= 0) {
                                                                          goto end;
                                                                        }
#line 445
                                                                        s__state = 4352;
#line 446
                                                                        __cil_tmp57 = (long )s__s3__flags;
#line 446
                                                                        __cil_tmp58 = __cil_tmp57 + 5L;
#line 446
                                                                        s__s3__flags = (int )__cil_tmp58;
#line 447
                                                                        if (s__hit) {
#line 448
                                                                          s__s3__tmp__next_state___0 = 3;
                                                                          {
#line 449
                                                                          __cil_tmp59 = (long )s__s3__flags;
#line 449
                                                                          if (__cil_tmp59 - 2L) {
#line 450
                                                                            s__state = 3;
#line 451
                                                                            __cil_tmp60 = (long )s__s3__flags;
#line 451
                                                                            __cil_tmp61 = __cil_tmp60 + 4L;
#line 451
                                                                            s__s3__flags = (int )__cil_tmp61;
#line 452
                                                                            s__s3__delay_buf_pop_ret = 0;
                                                                          }
                                                                          }
                                                                        } else {
#line 457
                                                                          s__s3__tmp__next_state___0 = 4560;
                                                                        }
#line 459
                                                                        s__init_num = 0;
                                                                        goto switch_1_break;
                                                                        switch_1_4560: ;
                                                                        switch_1_4561: 
#line 463
                                                                        ret = nse_symbolic_int();
#line 464
                                                                        if (ret <= 0) {
                                                                          goto end;
                                                                        }
#line 469
                                                                        if (s__hit) {
#line 470
                                                                          s__state = 4512;
                                                                        } else {
#line 472
                                                                          s__state = 3;
                                                                        }
#line 474
                                                                        s__init_num = 0;
                                                                        goto switch_1_break;
                                                                        switch_1_4352: 
                                                                        {
#line 477
                                                                        __cil_tmp62 = (long )num1;
#line 477
                                                                        if (__cil_tmp62 > 0L) {
#line 478
                                                                          s__rwstate = 2;
#line 479
                                                                          num1 = tmp___9;
                                                                          {
#line 480
                                                                          __cil_tmp63 = (long )num1;
#line 480
                                                                          if (__cil_tmp63 <= 0L) {
#line 481
                                                                            ret = -1;
                                                                            goto end;
                                                                          }
                                                                          }
#line 486
                                                                          s__rwstate = 1;
                                                                        }
                                                                        }
#line 490
                                                                        s__state = s__s3__tmp__next_state___0;
                                                                        goto switch_1_break;
                                                                        switch_1_3: 
#line 493
                                                                        if (s__init_buf___0 != 0) {
#line 494
                                                                          s__init_buf___0 = 0;
                                                                        }
                                                                        {
#line 498
                                                                        __cil_tmp64 = (long )s__s3__flags;
#line 498
                                                                        __cil_tmp65 = __cil_tmp64 - 4L;
#line 498
                                                                        if (! __cil_tmp65) {

                                                                        }
                                                                        }
#line 503
                                                                        s__init_num = 0;
#line 504
                                                                        s__new_session = 0;
#line 505
                                                                        if (s__hit) {
#line 506
                                                                          s__ctx__stats__sess_hit ++;
                                                                        }
#line 510
                                                                        ret = 1;
#line 511
                                                                        s__ctx__stats__sess_connect_good ++;
#line 512
                                                                        if (cb != 0) {

                                                                        }
                                                                        goto end;
                                                                        switch_1_default: 
#line 519
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
#line 558
    if (! s__s3__tmp__reuse_message) {
#line 559
      if (! skip) {
#line 560
        if (s__debug) {
#line 561
          ret = nse_symbolic_int();
#line 562
          if (ret <= 0) {
            goto end;
          }
        }
#line 570
        if (cb != 0) {
#line 571
          if (s__state != state) {
#line 572
            new_state = s__state;
#line 573
            s__state = state;
#line 574
            s__state = new_state;
          }
        }
      }
    }
#line 587
    skip = 0;
  }
  while_0_break: /* CIL Label */ ;
  }

  end: 
#line 592
  s__in_handshake --;
#line 593
  if (cb != 0) {

  }
#line 598
  return (ret);
}
}
#line 603 "s3_clnt_2_BUG.cil.c"
int main() 
{ int s ;

  {
  {
#line 608
  s = 12292;
#line 609
  ssl3_connect(s);
  }
#line 611
  return (0);
}
}
