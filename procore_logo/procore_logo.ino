#include <avr/pgmspace.h>  // Needed to store stuff in Flash using PROGMEM
#include "FastLED.h"       // Fastled library to control the LEDs
#include "pixelset.h"

#define NUM_LEDS 1024      // 32x32 board 
#define DATA_PIN 2         // must match the data outpin number you're using on your Arduino board

template<int SIZE>
class CustomCRGBArray : public CRGBArray<SIZE> {
public:  
    /// access a single element in this set, just like an array operator
    inline CRGB & operator[](int n) const { 
      int x = n == 0 ? 1023
            : n == 1 ? 1022
            : n == 2 ? 1021
            : n == 3 ? 1020
            : n == 4 ? 1019
            : n == 5 ? 1018
            : n == 6 ? 1017
            : n == 7 ? 1016
            : n == 8 ? 1015
            : n == 9 ? 1014
            : n == 10 ? 1013
            : n == 11 ? 1012
            : n == 12 ? 1011
            : n == 13 ? 1010
            : n == 14 ? 1009
            : n == 15 ? 1008
            : n == 16 ? 15
            : n == 17 ? 14
            : n == 18 ? 13
            : n == 19 ? 12
            : n == 20 ? 11
            : n == 21 ? 10
            : n == 22 ? 9
            : n == 23 ? 8
            : n == 24 ? 7
            : n == 25 ? 6
            : n == 26 ? 5
            : n == 27 ? 4
            : n == 28 ? 3
            : n == 29 ? 2
            : n == 30 ? 1
            : n == 31 ? 0
            : n == 32 ? 992
            : n == 33 ? 993
            : n == 34 ? 994
            : n == 35 ? 995
            : n == 36 ? 996
            : n == 37 ? 997
            : n == 38 ? 998
            : n == 39 ? 999
            : n == 40 ? 1000
            : n == 41 ? 1001
            : n == 42 ? 1002
            : n == 43 ? 1003
            : n == 44 ? 1004
            : n == 45 ? 1005
            : n == 46 ? 1006
            : n == 47 ? 1007
            : n == 48 ? 16
            : n == 49 ? 17
            : n == 50 ? 18
            : n == 51 ? 19
            : n == 52 ? 20
            : n == 53 ? 21
            : n == 54 ? 22
            : n == 55 ? 23
            : n == 56 ? 24
            : n == 57 ? 25
            : n == 58 ? 26
            : n == 59 ? 27
            : n == 60 ? 28
            : n == 61 ? 29
            : n == 62 ? 30
            : n == 63 ? 31
            : n == 64 ? 991
            : n == 65 ? 990
            : n == 66 ? 989
            : n == 67 ? 988
            : n == 68 ? 987
            : n == 69 ? 986
            : n == 70 ? 985
            : n == 71 ? 984
            : n == 72 ? 983
            : n == 73 ? 982
            : n == 74 ? 981
            : n == 75 ? 980
            : n == 76 ? 979
            : n == 77 ? 978
            : n == 78 ? 977
            : n == 79 ? 976
            : n == 80 ? 47
            : n == 81 ? 46
            : n == 82 ? 45
            : n == 83 ? 44
            : n == 84 ? 43
            : n == 85 ? 42
            : n == 86 ? 41
            : n == 87 ? 40
            : n == 88 ? 39
            : n == 89 ? 38
            : n == 90 ? 37
            : n == 91 ? 36
            : n == 92 ? 35
            : n == 93 ? 34
            : n == 94 ? 33
            : n == 95 ? 32
            : n == 96 ? 960
            : n == 97 ? 961
            : n == 98 ? 962
            : n == 99 ? 963
            : n == 100 ? 964
            : n == 101 ? 965
            : n == 102 ? 966
            : n == 103 ? 967
            : n == 104 ? 968
            : n == 105 ? 969
            : n == 106 ? 970
            : n == 107 ? 971
            : n == 108 ? 972
            : n == 109 ? 973
            : n == 110 ? 974
            : n == 111 ? 975
            : n == 112 ? 48
            : n == 113 ? 49
            : n == 114 ? 50
            : n == 115 ? 51
            : n == 116 ? 52
            : n == 117 ? 53
            : n == 118 ? 54
            : n == 119 ? 55
            : n == 120 ? 56
            : n == 121 ? 57
            : n == 122 ? 58
            : n == 123 ? 59
            : n == 124 ? 60
            : n == 125 ? 61
            : n == 126 ? 62
            : n == 127 ? 63
            : n == 128 ? 959
            : n == 129 ? 958
            : n == 130 ? 957
            : n == 131 ? 956
            : n == 132 ? 955
            : n == 133 ? 954
            : n == 134 ? 953
            : n == 135 ? 952
            : n == 136 ? 951
            : n == 137 ? 950
            : n == 138 ? 949
            : n == 139 ? 948
            : n == 140 ? 947
            : n == 141 ? 946
            : n == 142 ? 945
            : n == 143 ? 944
            : n == 144 ? 79
            : n == 145 ? 78
            : n == 146 ? 77
            : n == 147 ? 76
            : n == 148 ? 75
            : n == 149 ? 74
            : n == 150 ? 73
            : n == 151 ? 72
            : n == 152 ? 71
            : n == 153 ? 70
            : n == 154 ? 69
            : n == 155 ? 68
            : n == 156 ? 67
            : n == 157 ? 66
            : n == 158 ? 65
            : n == 159 ? 64
            : n == 160 ? 928
            : n == 161 ? 929
            : n == 162 ? 930
            : n == 163 ? 931
            : n == 164 ? 932
            : n == 165 ? 933
            : n == 166 ? 934
            : n == 167 ? 935
            : n == 168 ? 936
            : n == 169 ? 937
            : n == 170 ? 938
            : n == 171 ? 939
            : n == 172 ? 940
            : n == 173 ? 941
            : n == 174 ? 942
            : n == 175 ? 943
            : n == 176 ? 80
            : n == 177 ? 81
            : n == 178 ? 82
            : n == 179 ? 83
            : n == 180 ? 84
            : n == 181 ? 85
            : n == 182 ? 86
            : n == 183 ? 87
            : n == 184 ? 88
            : n == 185 ? 89
            : n == 186 ? 90
            : n == 187 ? 91
            : n == 188 ? 92
            : n == 189 ? 93
            : n == 190 ? 94
            : n == 191 ? 95
            : n == 192 ? 927
            : n == 193 ? 926
            : n == 194 ? 925
            : n == 195 ? 924
            : n == 196 ? 923
            : n == 197 ? 922
            : n == 198 ? 921
            : n == 199 ? 920
            : n == 200 ? 919
            : n == 201 ? 918
            : n == 202 ? 917
            : n == 203 ? 916
            : n == 204 ? 915
            : n == 205 ? 914
            : n == 206 ? 913
            : n == 207 ? 912
            : n == 208 ? 111
            : n == 209 ? 110
            : n == 210 ? 109
            : n == 211 ? 108
            : n == 212 ? 107
            : n == 213 ? 106
            : n == 214 ? 105
            : n == 215 ? 104
            : n == 216 ? 103
            : n == 217 ? 102
            : n == 218 ? 101
            : n == 219 ? 100
            : n == 220 ? 99
            : n == 221 ? 98
            : n == 222 ? 97
            : n == 223 ? 96
            : n == 224 ? 896
            : n == 225 ? 897
            : n == 226 ? 898
            : n == 227 ? 899
            : n == 228 ? 900
            : n == 229 ? 901
            : n == 230 ? 902
            : n == 231 ? 903
            : n == 232 ? 904
            : n == 233 ? 905
            : n == 234 ? 906
            : n == 235 ? 907
            : n == 236 ? 908
            : n == 237 ? 909
            : n == 238 ? 910
            : n == 239 ? 911
            : n == 240 ? 112
            : n == 241 ? 113
            : n == 242 ? 114
            : n == 243 ? 115
            : n == 244 ? 116
            : n == 245 ? 117
            : n == 246 ? 118
            : n == 247 ? 119
            : n == 248 ? 120
            : n == 249 ? 121
            : n == 250 ? 122
            : n == 251 ? 123
            : n == 252 ? 124
            : n == 253 ? 125
            : n == 254 ? 126
            : n == 255 ? 127
            : n == 256 ? 895
            : n == 257 ? 894
            : n == 258 ? 893
            : n == 259 ? 892
            : n == 260 ? 891
            : n == 261 ? 890
            : n == 262 ? 889
            : n == 263 ? 888
            : n == 264 ? 887
            : n == 265 ? 886
            : n == 266 ? 885
            : n == 267 ? 884
            : n == 268 ? 883
            : n == 269 ? 882
            : n == 270 ? 881
            : n == 271 ? 880
            : n == 272 ? 143
            : n == 273 ? 142
            : n == 274 ? 141
            : n == 275 ? 140
            : n == 276 ? 139
            : n == 277 ? 138
            : n == 278 ? 137
            : n == 279 ? 136
            : n == 280 ? 135
            : n == 281 ? 134
            : n == 282 ? 133
            : n == 283 ? 132
            : n == 284 ? 131
            : n == 285 ? 130
            : n == 286 ? 129
            : n == 287 ? 128
            : n == 288 ? 864
            : n == 289 ? 865
            : n == 290 ? 866
            : n == 291 ? 867
            : n == 292 ? 868
            : n == 293 ? 869
            : n == 294 ? 870
            : n == 295 ? 871
            : n == 296 ? 872
            : n == 297 ? 873
            : n == 298 ? 874
            : n == 299 ? 875
            : n == 300 ? 876
            : n == 301 ? 877
            : n == 302 ? 878
            : n == 303 ? 879
            : n == 304 ? 144
            : n == 305 ? 145
            : n == 306 ? 146
            : n == 307 ? 147
            : n == 308 ? 148
            : n == 309 ? 149
            : n == 310 ? 150
            : n == 311 ? 151
            : n == 312 ? 152
            : n == 313 ? 153
            : n == 314 ? 154
            : n == 315 ? 155
            : n == 316 ? 156
            : n == 317 ? 157
            : n == 318 ? 158
            : n == 319 ? 159
            : n == 320 ? 863
            : n == 321 ? 862
            : n == 322 ? 861
            : n == 323 ? 860
            : n == 324 ? 859
            : n == 325 ? 858
            : n == 326 ? 857
            : n == 327 ? 856
            : n == 328 ? 855
            : n == 329 ? 854
            : n == 330 ? 853
            : n == 331 ? 852
            : n == 332 ? 851
            : n == 333 ? 850
            : n == 334 ? 849
            : n == 335 ? 848
            : n == 336 ? 175
            : n == 337 ? 174
            : n == 338 ? 173
            : n == 339 ? 172
            : n == 340 ? 171
            : n == 341 ? 170
            : n == 342 ? 169
            : n == 343 ? 168
            : n == 344 ? 167
            : n == 345 ? 166
            : n == 346 ? 165
            : n == 347 ? 164
            : n == 348 ? 163
            : n == 349 ? 162
            : n == 350 ? 161
            : n == 351 ? 160
            : n == 352 ? 832
            : n == 353 ? 833
            : n == 354 ? 834
            : n == 355 ? 835
            : n == 356 ? 836
            : n == 357 ? 837
            : n == 358 ? 838
            : n == 359 ? 839
            : n == 360 ? 840
            : n == 361 ? 841
            : n == 362 ? 842
            : n == 363 ? 843
            : n == 364 ? 844
            : n == 365 ? 845
            : n == 366 ? 846
            : n == 367 ? 847
            : n == 368 ? 176
            : n == 369 ? 177
            : n == 370 ? 178
            : n == 371 ? 179
            : n == 372 ? 180
            : n == 373 ? 181
            : n == 374 ? 182
            : n == 375 ? 183
            : n == 376 ? 184
            : n == 377 ? 185
            : n == 378 ? 186
            : n == 379 ? 187
            : n == 380 ? 188
            : n == 381 ? 189
            : n == 382 ? 190
            : n == 383 ? 191
            : n == 384 ? 831
            : n == 385 ? 830
            : n == 386 ? 829
            : n == 387 ? 828
            : n == 388 ? 827
            : n == 389 ? 826
            : n == 390 ? 825
            : n == 391 ? 824
            : n == 392 ? 823
            : n == 393 ? 822
            : n == 394 ? 821
            : n == 395 ? 820
            : n == 396 ? 819
            : n == 397 ? 818
            : n == 398 ? 817
            : n == 399 ? 816
            : n == 400 ? 207
            : n == 401 ? 206
            : n == 402 ? 205
            : n == 403 ? 204
            : n == 404 ? 203
            : n == 405 ? 202
            : n == 406 ? 201
            : n == 407 ? 200
            : n == 408 ? 199
            : n == 409 ? 198
            : n == 410 ? 197
            : n == 411 ? 196
            : n == 412 ? 195
            : n == 413 ? 194
            : n == 414 ? 193
            : n == 415 ? 192
            : n == 416 ? 800
            : n == 417 ? 801
            : n == 418 ? 802
            : n == 419 ? 803
            : n == 420 ? 804
            : n == 421 ? 805
            : n == 422 ? 806
            : n == 423 ? 807
            : n == 424 ? 808
            : n == 425 ? 809
            : n == 426 ? 810
            : n == 427 ? 811
            : n == 428 ? 812
            : n == 429 ? 813
            : n == 430 ? 814
            : n == 431 ? 815
            : n == 432 ? 208
            : n == 433 ? 209
            : n == 434 ? 210
            : n == 435 ? 211
            : n == 436 ? 212
            : n == 437 ? 213
            : n == 438 ? 214
            : n == 439 ? 215
            : n == 440 ? 216
            : n == 441 ? 217
            : n == 442 ? 218
            : n == 443 ? 219
            : n == 444 ? 220
            : n == 445 ? 221
            : n == 446 ? 222
            : n == 447 ? 223
            : n == 448 ? 799
            : n == 449 ? 798
            : n == 450 ? 797
            : n == 451 ? 796
            : n == 452 ? 795
            : n == 453 ? 794
            : n == 454 ? 793
            : n == 455 ? 792
            : n == 456 ? 791
            : n == 457 ? 790
            : n == 458 ? 789
            : n == 459 ? 788
            : n == 460 ? 787
            : n == 461 ? 786
            : n == 462 ? 785
            : n == 463 ? 784
            : n == 464 ? 239
            : n == 465 ? 238
            : n == 466 ? 237
            : n == 467 ? 236
            : n == 468 ? 235
            : n == 469 ? 234
            : n == 470 ? 233
            : n == 471 ? 232
            : n == 472 ? 231
            : n == 473 ? 230
            : n == 474 ? 229
            : n == 475 ? 228
            : n == 476 ? 227
            : n == 477 ? 226
            : n == 478 ? 225
            : n == 479 ? 224
            : n == 480 ? 768
            : n == 481 ? 769
            : n == 482 ? 770
            : n == 483 ? 771
            : n == 484 ? 772
            : n == 485 ? 773
            : n == 486 ? 774
            : n == 487 ? 775
            : n == 488 ? 776
            : n == 489 ? 777
            : n == 490 ? 778
            : n == 491 ? 779
            : n == 492 ? 780
            : n == 493 ? 781
            : n == 494 ? 782
            : n == 495 ? 783
            : n == 496 ? 240
            : n == 497 ? 241
            : n == 498 ? 242
            : n == 499 ? 243
            : n == 500 ? 244
            : n == 501 ? 245
            : n == 502 ? 246
            : n == 503 ? 247
            : n == 504 ? 248
            : n == 505 ? 249
            : n == 506 ? 250
            : n == 507 ? 251
            : n == 508 ? 252
            : n == 509 ? 253
            : n == 510 ? 254
            : n == 511 ? 255
            : n == 512 ? 767
            : n == 513 ? 766
            : n == 514 ? 765
            : n == 515 ? 764
            : n == 516 ? 763
            : n == 517 ? 762
            : n == 518 ? 761
            : n == 519 ? 760
            : n == 520 ? 759
            : n == 521 ? 758
            : n == 522 ? 757
            : n == 523 ? 756
            : n == 524 ? 755
            : n == 525 ? 754
            : n == 526 ? 753
            : n == 527 ? 752
            : n == 528 ? 271
            : n == 529 ? 270
            : n == 530 ? 269
            : n == 531 ? 268
            : n == 532 ? 267
            : n == 533 ? 266
            : n == 534 ? 265
            : n == 535 ? 264
            : n == 536 ? 263
            : n == 537 ? 262
            : n == 538 ? 261
            : n == 539 ? 260
            : n == 540 ? 259
            : n == 541 ? 258
            : n == 542 ? 257
            : n == 543 ? 256
            : n == 544 ? 736
            : n == 545 ? 737
            : n == 546 ? 738
            : n == 547 ? 739
            : n == 548 ? 740
            : n == 549 ? 741
            : n == 550 ? 742
            : n == 551 ? 743
            : n == 552 ? 744
            : n == 553 ? 745
            : n == 554 ? 746
            : n == 555 ? 747
            : n == 556 ? 748
            : n == 557 ? 749
            : n == 558 ? 750
            : n == 559 ? 751
            : n == 560 ? 272
            : n == 561 ? 273
            : n == 562 ? 274
            : n == 563 ? 275
            : n == 564 ? 276
            : n == 565 ? 277
            : n == 566 ? 278
            : n == 567 ? 279
            : n == 568 ? 280
            : n == 569 ? 281
            : n == 570 ? 282
            : n == 571 ? 283
            : n == 572 ? 284
            : n == 573 ? 285
            : n == 574 ? 286
            : n == 575 ? 287
            : n == 576 ? 735
            : n == 577 ? 734
            : n == 578 ? 733
            : n == 579 ? 732
            : n == 580 ? 731
            : n == 581 ? 730
            : n == 582 ? 729
            : n == 583 ? 728
            : n == 584 ? 727
            : n == 585 ? 726
            : n == 586 ? 725
            : n == 587 ? 724
            : n == 588 ? 723
            : n == 589 ? 722
            : n == 590 ? 721
            : n == 591 ? 720
            : n == 592 ? 303
            : n == 593 ? 302
            : n == 594 ? 301
            : n == 595 ? 300
            : n == 596 ? 299
            : n == 597 ? 298
            : n == 598 ? 297
            : n == 599 ? 296
            : n == 600 ? 295
            : n == 601 ? 294
            : n == 602 ? 293
            : n == 603 ? 292
            : n == 604 ? 291
            : n == 605 ? 290
            : n == 606 ? 289
            : n == 607 ? 288
            : n == 608 ? 704
            : n == 609 ? 705
            : n == 610 ? 706
            : n == 611 ? 707
            : n == 612 ? 708
            : n == 613 ? 709
            : n == 614 ? 710
            : n == 615 ? 711
            : n == 616 ? 712
            : n == 617 ? 713
            : n == 618 ? 714
            : n == 619 ? 715
            : n == 620 ? 716
            : n == 621 ? 717
            : n == 622 ? 718
            : n == 623 ? 719
            : n == 624 ? 304
            : n == 625 ? 305
            : n == 626 ? 306
            : n == 627 ? 307
            : n == 628 ? 308
            : n == 629 ? 309
            : n == 630 ? 310
            : n == 631 ? 311
            : n == 632 ? 312
            : n == 633 ? 313
            : n == 634 ? 314
            : n == 635 ? 315
            : n == 636 ? 316
            : n == 637 ? 317
            : n == 638 ? 318
            : n == 639 ? 319
            : n == 640 ? 703
            : n == 641 ? 702
            : n == 642 ? 701
            : n == 643 ? 700
            : n == 644 ? 699
            : n == 645 ? 698
            : n == 646 ? 697
            : n == 647 ? 696
            : n == 648 ? 695
            : n == 649 ? 694
            : n == 650 ? 693
            : n == 651 ? 692
            : n == 652 ? 691
            : n == 653 ? 690
            : n == 654 ? 689
            : n == 655 ? 688
            : n == 656 ? 335
            : n == 657 ? 334
            : n == 658 ? 333
            : n == 659 ? 332
            : n == 660 ? 331
            : n == 661 ? 330
            : n == 662 ? 329
            : n == 663 ? 328
            : n == 664 ? 327
            : n == 665 ? 326
            : n == 666 ? 325
            : n == 667 ? 324
            : n == 668 ? 323
            : n == 669 ? 322
            : n == 670 ? 321
            : n == 671 ? 320
            : n == 672 ? 672
            : n == 673 ? 673
            : n == 674 ? 674
            : n == 675 ? 675
            : n == 676 ? 676
            : n == 677 ? 677
            : n == 678 ? 678
            : n == 679 ? 679
            : n == 680 ? 680
            : n == 681 ? 681
            : n == 682 ? 682
            : n == 683 ? 683
            : n == 684 ? 684
            : n == 685 ? 685
            : n == 686 ? 686
            : n == 687 ? 687
            : n == 688 ? 336
            : n == 689 ? 337
            : n == 690 ? 338
            : n == 691 ? 339
            : n == 692 ? 340
            : n == 693 ? 341
            : n == 694 ? 342
            : n == 695 ? 343
            : n == 696 ? 344
            : n == 697 ? 345
            : n == 698 ? 346
            : n == 699 ? 347
            : n == 700 ? 348
            : n == 701 ? 349
            : n == 702 ? 350
            : n == 703 ? 351
            : n == 704 ? 671
            : n == 705 ? 670
            : n == 706 ? 669
            : n == 707 ? 668
            : n == 708 ? 667
            : n == 709 ? 666
            : n == 710 ? 665
            : n == 711 ? 664
            : n == 712 ? 663
            : n == 713 ? 662
            : n == 714 ? 661
            : n == 715 ? 660
            : n == 716 ? 659
            : n == 717 ? 658
            : n == 718 ? 657
            : n == 719 ? 656
            : n == 720 ? 367
            : n == 721 ? 366
            : n == 722 ? 365
            : n == 723 ? 364
            : n == 724 ? 363
            : n == 725 ? 362
            : n == 726 ? 361
            : n == 727 ? 360
            : n == 728 ? 359
            : n == 729 ? 358
            : n == 730 ? 357
            : n == 731 ? 356
            : n == 732 ? 355
            : n == 733 ? 354
            : n == 734 ? 353
            : n == 735 ? 352
            : n == 736 ? 640
            : n == 737 ? 641
            : n == 738 ? 642
            : n == 739 ? 643
            : n == 740 ? 644
            : n == 741 ? 645
            : n == 742 ? 646
            : n == 743 ? 647
            : n == 744 ? 648
            : n == 745 ? 649
            : n == 746 ? 650
            : n == 747 ? 651
            : n == 748 ? 652
            : n == 749 ? 653
            : n == 750 ? 654
            : n == 751 ? 655
            : n == 752 ? 368
            : n == 753 ? 369
            : n == 754 ? 370
            : n == 755 ? 371
            : n == 756 ? 372
            : n == 757 ? 373
            : n == 758 ? 374
            : n == 759 ? 375
            : n == 760 ? 376
            : n == 761 ? 377
            : n == 762 ? 378
            : n == 763 ? 379
            : n == 764 ? 380
            : n == 765 ? 381
            : n == 766 ? 382
            : n == 767 ? 383
            : n == 768 ? 639
            : n == 769 ? 638
            : n == 770 ? 637
            : n == 771 ? 636
            : n == 772 ? 635
            : n == 773 ? 634
            : n == 774 ? 633
            : n == 775 ? 632
            : n == 776 ? 631
            : n == 777 ? 630
            : n == 778 ? 629
            : n == 779 ? 628
            : n == 780 ? 627
            : n == 781 ? 626
            : n == 782 ? 625
            : n == 783 ? 624
            : n == 784 ? 399
            : n == 785 ? 398
            : n == 786 ? 397
            : n == 787 ? 396
            : n == 788 ? 395
            : n == 789 ? 394
            : n == 790 ? 393
            : n == 791 ? 392
            : n == 792 ? 391
            : n == 793 ? 390
            : n == 794 ? 389
            : n == 795 ? 388
            : n == 796 ? 387
            : n == 797 ? 386
            : n == 798 ? 385
            : n == 799 ? 384
            : n == 800 ? 608
            : n == 801 ? 609
            : n == 802 ? 610
            : n == 803 ? 611
            : n == 804 ? 612
            : n == 805 ? 613
            : n == 806 ? 614
            : n == 807 ? 615
            : n == 808 ? 616
            : n == 809 ? 617
            : n == 810 ? 618
            : n == 811 ? 619
            : n == 812 ? 620
            : n == 813 ? 621
            : n == 814 ? 622
            : n == 815 ? 623
            : n == 816 ? 400
            : n == 817 ? 401
            : n == 818 ? 402
            : n == 819 ? 403
            : n == 820 ? 404
            : n == 821 ? 405
            : n == 822 ? 406
            : n == 823 ? 407
            : n == 824 ? 408
            : n == 825 ? 409
            : n == 826 ? 410
            : n == 827 ? 411
            : n == 828 ? 412
            : n == 829 ? 413
            : n == 830 ? 414
            : n == 831 ? 415
            : n == 832 ? 607
            : n == 833 ? 606
            : n == 834 ? 605
            : n == 835 ? 604
            : n == 836 ? 603
            : n == 837 ? 602
            : n == 838 ? 601
            : n == 839 ? 600
            : n == 840 ? 599
            : n == 841 ? 598
            : n == 842 ? 597
            : n == 843 ? 596
            : n == 844 ? 595
            : n == 845 ? 594
            : n == 846 ? 593
            : n == 847 ? 592
            : n == 848 ? 431
            : n == 849 ? 430
            : n == 850 ? 429
            : n == 851 ? 428
            : n == 852 ? 427
            : n == 853 ? 426
            : n == 854 ? 425
            : n == 855 ? 424
            : n == 856 ? 423
            : n == 857 ? 422
            : n == 858 ? 421
            : n == 859 ? 420
            : n == 860 ? 419
            : n == 861 ? 418
            : n == 862 ? 417
            : n == 863 ? 416
            : n == 864 ? 576
            : n == 865 ? 577
            : n == 866 ? 578
            : n == 867 ? 579
            : n == 868 ? 580
            : n == 869 ? 581
            : n == 870 ? 582
            : n == 871 ? 583
            : n == 872 ? 584
            : n == 873 ? 585
            : n == 874 ? 586
            : n == 875 ? 587
            : n == 876 ? 588
            : n == 877 ? 589
            : n == 878 ? 590
            : n == 879 ? 591
            : n == 880 ? 432
            : n == 881 ? 433
            : n == 882 ? 434
            : n == 883 ? 435
            : n == 884 ? 436
            : n == 885 ? 437
            : n == 886 ? 438
            : n == 887 ? 439
            : n == 888 ? 440
            : n == 889 ? 441
            : n == 890 ? 442
            : n == 891 ? 443
            : n == 892 ? 444
            : n == 893 ? 445
            : n == 894 ? 446
            : n == 895 ? 447
            : n == 896 ? 575
            : n == 897 ? 574
            : n == 898 ? 573
            : n == 899 ? 572
            : n == 900 ? 571
            : n == 901 ? 570
            : n == 902 ? 569
            : n == 903 ? 568
            : n == 904 ? 567
            : n == 905 ? 566
            : n == 906 ? 565
            : n == 907 ? 564
            : n == 908 ? 563
            : n == 909 ? 562
            : n == 910 ? 561
            : n == 911 ? 560
            : n == 912 ? 463
            : n == 913 ? 462
            : n == 914 ? 461
            : n == 915 ? 460
            : n == 916 ? 459
            : n == 917 ? 458
            : n == 918 ? 457
            : n == 919 ? 456
            : n == 920 ? 455
            : n == 921 ? 454
            : n == 922 ? 453
            : n == 923 ? 452
            : n == 924 ? 451
            : n == 925 ? 450
            : n == 926 ? 449
            : n == 927 ? 448
            : n == 928 ? 544
            : n == 929 ? 545
            : n == 930 ? 546
            : n == 931 ? 547
            : n == 932 ? 548
            : n == 933 ? 549
            : n == 934 ? 550
            : n == 935 ? 551
            : n == 936 ? 552
            : n == 937 ? 553
            : n == 938 ? 554
            : n == 939 ? 555
            : n == 940 ? 556
            : n == 941 ? 557
            : n == 942 ? 558
            : n == 943 ? 559
            : n == 944 ? 464
            : n == 945 ? 465
            : n == 946 ? 466
            : n == 947 ? 467
            : n == 948 ? 468
            : n == 949 ? 469
            : n == 950 ? 470
            : n == 951 ? 471
            : n == 952 ? 472
            : n == 953 ? 473
            : n == 954 ? 474
            : n == 955 ? 475
            : n == 956 ? 476
            : n == 957 ? 477
            : n == 958 ? 478
            : n == 959 ? 479
            : n == 960 ? 543
            : n == 961 ? 542
            : n == 962 ? 541
            : n == 963 ? 540
            : n == 964 ? 539
            : n == 965 ? 538
            : n == 966 ? 537
            : n == 967 ? 536
            : n == 968 ? 535
            : n == 969 ? 534
            : n == 970 ? 533
            : n == 971 ? 532
            : n == 972 ? 531
            : n == 973 ? 530
            : n == 974 ? 529
            : n == 975 ? 528
            : n == 976 ? 495
            : n == 977 ? 494
            : n == 978 ? 493
            : n == 979 ? 492
            : n == 980 ? 491
            : n == 981 ? 490
            : n == 982 ? 489
            : n == 983 ? 488
            : n == 984 ? 487
            : n == 985 ? 486
            : n == 986 ? 485
            : n == 987 ? 484
            : n == 988 ? 483
            : n == 989 ? 482
            : n == 990 ? 481
            : n == 991 ? 480
            : n == 992 ? 512
            : n == 993 ? 513
            : n == 994 ? 514
            : n == 995 ? 515
            : n == 996 ? 516
            : n == 997 ? 517
            : n == 998 ? 518
            : n == 999 ? 519
            : n == 1000 ? 520
            : n == 1001 ? 521
            : n == 1002 ? 522
            : n == 1003 ? 523
            : n == 1004 ? 524
            : n == 1005 ? 525
            : n == 1006 ? 526
            : n == 1007 ? 527
            : n == 1008 ? 496
            : n == 1009 ? 497
            : n == 1010 ? 498
            : n == 1011 ? 499
            : n == 1012 ? 500
            : n == 1013 ? 501
            : n == 1014 ? 502
            : n == 1015 ? 503
            : n == 1016 ? 504
            : n == 1017 ? 505
            : n == 1018 ? 506
            : n == 1019 ? 507
            : n == 1020 ? 508
            : n == 1021 ? 509
            : n == 1022 ? 510
            : n == 1023 ? 511
            : 0;

      return CRGBArray<SIZE>::operator[](x);
    }
};

class Picture {
  public:

  Picture(CustomCRGBArray<NUM_LEDS> *leds, const long *image, int width, int height, int x, int y, int x_offset, int y_offset, bool isBitmask = false) {
    this->leds = leds;
    this->image = image;
    this->width = width;
    this->height = height;
    this->x = x;
    this->y = x;
    this->x_offset = x_offset;
    this->y_offset = y_offset;
    this->isBitmask = isBitmask;
  }

  void drawImage() {
    this->updateImageLocation();

    // render the image
    for (int j=this->y; j<this->y+this->height; j++) {
      for (int i=this->x; i<this->x+this->width; i++) {
        int image_index = (i-x) + (j-y) * this->width;
        int led_index = i + j * 32;
        if (this->isBitmask) {
          if (pgm_read_dword(&(this->image[image_index]))) {
            (*this->leds)[led_index] = 0xFF0000;
          }
        } else {
          (*this->leds)[led_index] = pgm_read_dword(&(this->image[image_index]));
        }
      }
    }
  }

  void clearImage() {
    for (int i=this->x; i<this->x+this->width; i++) {
      for (int j=this->y; j<this->y+this->height; j++) {
        int led_index = i + j * 32;
        (*this->leds)[led_index] = CRGB::Black;
      }
    }
  }

  void updateImageLocation() { // "tick" forward the image's drifting motion across the grid
    if (this->x + this->x_offset > 32 - this->width || this->x + this->x_offset < 0) {
      if (this->x + this->x_offset < 0) {
        this->x++;
      }
      this->x_offset = -this->x_offset;
    }
    this->x += this->x_offset;

    if (this->y + this->y_offset > 32 - this->height || this->y + this->y_offset < 0) {
      this->y_offset = -this->y_offset;
    }
    if (this->y + this->y_offset < 0) {
      this->y++;
    }  
    this->y += this->y_offset;
  }

  private:
    CustomCRGBArray<NUM_LEDS> *leds;
    int width;
    int height;
    int x;
    int y;
    int x_offset;
    int y_offset;
    bool isBitmask;
    long *image;
};

CustomCRGBArray<NUM_LEDS> leds;
uint8_t gHue = 0; // rotating "base color" used by many of the patterns

const long Arlo[] PROGMEM = 
{ // 12x5
  1, 1, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0,
  1, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0,
  1, 1, 1, 0, 1, 1, 0, 1, 0, 1, 1, 1,
  1, 0, 1, 0, 1, 0, 0, 1, 0, 1, 0, 1,
  1, 0, 1, 0, 1, 0, 0, 1, 0, 1, 1, 1,
};

const long ProcoreLogo[] PROGMEM =  // 16x16 image 
{
  // Procore logo
  0xf4f5f6, 0xf4f5f6, 0x8d8e8e, 0x7c7e7f, 0x7c7e7f, 0x7c7e7f, 0x7c7e7f, 0x7c7e7f, 0x7c7e7f, 0x7c7e7f, 0x7c7e7f, 0x7c7e7f, 0x7c7e7f, 0x8d8e8e, 0xf4f5f6, 0xf4f5f6, 
  0xf4f5f6, 0x595d61, 0x161d26, 0x111821, 0x111821, 0x111821, 0x111821, 0x111821, 0x111821, 0x111821, 0x111821, 0x111821, 0x111821, 0x161d26, 0x595d61, 0xf4f5f6, 
  0x66686b, 0x121922, 0x111821, 0x111821, 0x111821, 0x111821, 0x111821, 0x111821, 0x111821, 0x111821, 0x111821, 0x111821, 0x111821, 0x111821, 0x121922, 0x66686b, 
  0x191f28, 0x111821, 0x111821, 0x111821, 0x111821, 0x41454c, 0x4f5357, 0x4f5357, 0x4f5357, 0x4f5357, 0x41454c, 0x111821, 0x111821, 0x111821, 0x111821, 0x191f28, 
  0x111821, 0x111821, 0x111821, 0x111821, 0x252a32, 0x949494, 0xf4f5f6, 0xf4f5f6, 0xf4f5f6, 0xf4f5f6, 0x949494, 0x252a32, 0x111821, 0x111821, 0x111821, 0x111821, 
  0x111821, 0x111821, 0x111821, 0x121922, 0x78797b, 0xf4f5f6, 0xac897d, 0xc07c67, 0xc07c67, 0xac897d, 0xf4f5f6, 0x78797b, 0x121922, 0x111821, 0x111821, 0x111821, 
  0x111821, 0x111821, 0x111821, 0x383d44, 0xf4f5f6, 0x9a9492, 0xf4561a, 0xfc5100, 0xfc5100, 0xf4561a, 0x9a9492, 0xf4f5f6, 0x8c8d8d, 0x8c8d8d, 0x8c8d8d, 0x8c8d8d,
  0x111821, 0x111821, 0x111821, 0x383d44, 0xf4f5f6, 0x9a9492, 0xf4561a, 0xfc5100, 0xfc5100, 0xf4561a, 0x9a9492, 0xf4f5f6, 0x8c8d8d, 0x8c8d8d, 0x8c8d8d, 0x8c8d8d, 
  0x111821, 0x111821, 0x151b24, 0x89898a, 0xf4f5f6, 0xcf7356, 0xfc5100, 0xfc5100, 0xfc5100, 0xfc5100, 0xcf7356, 0xf4f5f6, 0xf4f5f6, 0xf4f5f6, 0xf4f5f6, 0xf4f5f6,
  0x111821, 0x111821, 0x151b24, 0x89898a, 0xf4f5f6, 0xcf7356, 0xfc5100, 0xfc5100, 0xfc5100, 0xfc5100, 0xcf7356, 0xf4f5f6, 0xf4f5f6, 0xf4f5f6, 0xf4f5f6, 0xf4f5f6,
  0x111821, 0x111821, 0x111821, 0x121922, 0x78797b, 0xf4f5f6, 0xac897d, 0xc07c67, 0xc07c67, 0xac897d, 0xf4f5f6, 0x78797b, 0x121922, 0x111821, 0x111821, 0x111821,
  0x111821, 0x111821, 0x111821, 0x111821, 0x252a32, 0x949494, 0xf4f5f6, 0xf4f5f6, 0xf4f5f6, 0xf4f5f6, 0x949494, 0x252a32, 0x111821, 0x111821, 0x111821, 0x111821, 
  0x191f28, 0x111821, 0x111821, 0x111821, 0x111821, 0x41454c, 0x4f5357, 0x4f5357, 0x4f5357, 0x4f5357, 0x41454c, 0x111821, 0x111821, 0x111821, 0x111821, 0x191f28, 
  0x66686b, 0x121922, 0x111821, 0x111821, 0x111821, 0x111821, 0x111821, 0x111821, 0x111821, 0x111821, 0x111821, 0x111821, 0x111821, 0x111821, 0x121922, 0x66686b, 
  0xf4f5f6, 0x595d61, 0x161d26, 0x111821, 0x111821, 0x111821, 0x111821, 0x111821, 0x111821, 0x111821, 0x111821, 0x111821, 0x111821, 0x161d26, 0x595d61, 0xf4f5f6, 
  0xf4f5f6, 0xf4f5f6, 0x8d8e8e, 0x7c7e7f, 0x7c7e7f, 0x7c7e7f, 0x7c7e7f, 0x7c7e7f, 0x7c7e7f, 0x7c7e7f, 0x7c7e7f, 0x7c7e7f, 0x7c7e7f, 0x8d8e8e, 0xf4f5f6, 0xf4f5f6, 
};

const long Qbert[] PROGMEM = 
{
0x000000, 0x000000, 0x000000, 0x000000, 0xff6600, 0xff6600, 0xff6600, 0xff6600, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 
0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0xff0033, 0xff0033, 0xff0033, 0xff0033, 0xff0033, 0xff6600, 0xff6600, 0xff6600, 0x000000, 0x000000, 
0x000000, 0xff0033, 0xff0033, 0xff6600, 0xff0033, 0xffffff, 0xffffff, 0xff0033, 0xffffff, 0xffffff, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 
0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0xff0033, 0x000000, 0x000000, 0xff0033, 0xff6600, 0xff6600, 0xff0033, 0x000000, 
0xff0033, 0xff0033, 0xff0033, 0xff6600, 0xff0033, 0x000000, 0x000000, 0xff0033, 0x000000, 0x000000, 0xff6600, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 
0x000000, 0x000000, 0x000000, 0xff6600, 0xff6600, 0xff6600, 0xff6600, 0xff6600, 0xff6600, 0xff0033, 0xff0033, 0xff6600, 0xff6600, 0xff6600, 0xff0033, 0xff0033, 
0xff0033, 0xff0033, 0xff0033, 0xff6600, 0xff6600, 0xff6600, 0xff6600, 0xff6600, 0xff6600, 0xff6600, 0xff6600, 0xff6600, 0xff6600, 0xff6600, 0x000000, 0x000000, 
0x000000, 0xff6600, 0xff6600, 0xff6600, 0xff0033, 0xff0033, 0xff0033, 0xff6600, 0xff0033, 0xff6600, 0xff0033, 0xff6600, 0xff0033, 0xff6600, 0xff0033, 0xff0033,
0x000000, 0xff0033, 0xff0033, 0xff0033, 0xff0033, 0xff0033, 0xff6600, 0xff0033, 0xff0033, 0x000000, 0xff0033, 0xff0033, 0x000000, 0x000000, 0xff6600, 0x000000, 
0x000000, 0xff0033, 0x000000, 0x000000, 0xff0033, 0x000000, 0x000000, 0x000000, 0xff0033, 0xff0033, 0xff0033, 0xff0033, 0xff0033, 0xff0033, 0x000000, 0x000000, 
0x000000, 0x000000, 0x000000, 0xff0033, 0xff0033, 0xff0033, 0xff0033, 0xff0033, 0x000000, 0x000000, 0x000000, 0x000000, 0xff0033, 0xff0033, 0x000000, 0x000000, 
0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0xff0033, 0x000000, 0x000000, 0x000000, 0xff0033, 0x000000, 0x000000, 0x000000, 
0x000000, 0x000000, 0x000000, 0xff0033, 0x000000, 0x000000, 0x000000, 0xff0033, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 
0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0xff0033, 0x000000, 0x000000, 0x000000, 0xff0033, 0x000000, 0x000000, 0x000000,
0x000000, 0x000000, 0xff6600, 0xff6600, 0xff6600, 0x000000, 0x000000, 0xff0033, 0xff6600, 0xff6600, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 
0x000000, 0x000000, 0x000000, 0x000000, 0xff6600, 0xff6600, 0xff0033, 0x000000, 0x000000, 0xff6600, 0xff6600, 0xff6600, 0xff0033, 0x000000, 0x000000, 0x000000
};

Picture *arlo;
Picture *procoreLogo;

void setup() { 
  // Serial.begin(115200);  // DEBUGGERY
  FastLED.addLeds<NEOPIXEL,DATA_PIN>(leds, NUM_LEDS);  // initializes the FastLED library
  FastLED.setBrightness(25);
  FastLED.clear();

  arlo = new Picture(&leds, Arlo, 12, 5, 3, 0, 1, 1, true);
  procoreLogo = new Picture(&leds, ProcoreLogo, 16, 16, 15, 15, 1, 1);
}

void loop() {
  // fill_rainbow( leds, 1024, gHue, 7);

  // // a colored dot sweeping back and forth, with fading trails
  // fadeToBlackBy( leds, NUM_LEDS, 20);
  // int pos = beatsin16( 13, 0, NUM_LEDS-1 );
  // leds[pos] += CHSV( gHue, 255, 192);

  // // send the 'leds' array out to the actual LED strip
  // FastLED.show();  
  // // insert a delay to keep the framerate modest
  // //FastLED.delay(1000/120); 

  // // do some periodic updates
  // EVERY_N_MILLISECONDS( 20 ) { gHue++; } // slowly cycle the "base color" through the rainbow

  procoreLogo->drawImage();
  arlo->drawImage();

  FastLED.show();
  delay(20);

  procoreLogo->clearImage();
  arlo->clearImage();
}
