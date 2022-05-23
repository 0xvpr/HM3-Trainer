#ifndef ENTITY_HPP
#define ENTITY_HPP

#include <windows.h>
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

typedef struct _Vtable {
    void    (__thiscall * Function_0000)(void *); //#0 +0 .rdata:00796334
    void    (__thiscall * Function_0001)(void *); //#1 +4 .rdata:00796338
    void    (__thiscall * Function_0002)(void *); //#2 +8 .rdata:0079633c
    void    (__thiscall * Function_0003)(void *); //#3 +c .rdata:00796340
    void    (__thiscall * loadParameters)(void *); //#4 +10 .rdata:00796344
    void    (__thiscall * Function_0005)(void *); //#5 +14 .rdata:00796348
    void    (__thiscall * Function_0006)(void *); //#6 +18 .rdata:0079634c
    void    (__thiscall * Function_0007)(void *); //#7 +1c .rdata:00796350
    void    (__thiscall * Function_0008)(void *); //#8 +20 .rdata:00796354
    void    (__thiscall * Function_0009)(void *); //#9 +24 .rdata:00796358
    void    (__thiscall * Function_0010)(void *); //#10 +28 .rdata:0079635c
    void    (__thiscall * Function_0011)(void *); //#11 +2c .rdata:00796360
    void    (__thiscall * Function_0012)(void *); //#12 +30 .rdata:00796364
    void    (__thiscall * Function_0013)(void *); //#13 +34 .rdata:00796368
    void    (__thiscall * Function_0014)(void *); //#14 +38 .rdata:0079636c
    void    (__thiscall * Function_0015)(void *); //#15 +3c .rdata:00796370
    void    (__thiscall * Function_0016)(void *); //#16 +40 .rdata:00796374
    void    (__thiscall * Function_0017)(void *); //#17 +44 .rdata:00796378
    void    (__thiscall * Function_0018)(void *); //#18 +48 .rdata:0079637c
    void    (__thiscall * Function_0019)(void *); //#19 +4c .rdata:00796380
    void    (__thiscall * Function_0020)(void *); //#20 +50 .rdata:00796384
    void    (__thiscall * Function_0021)(void *); //#21 +54 .rdata:00796388
    void    (__thiscall * Function_0022)(void *); //#22 +58 .rdata:0079638c
    void    (__thiscall * Function_0023)(void *); //#23 +5c .rdata:00796390
    void    (__thiscall * Function_0024)(void *); //#24 +60 .rdata:00796394
    void    (__thiscall * Function_0025)(void *); //#25 +64 .rdata:00796398
    void    (__thiscall * Function_0026)(void *); //#26 +68 .rdata:0079639c
    void    (__thiscall * Function_0027)(void *); //#27 +6c .rdata:007963a0
    void    (__thiscall * Function_0028)(void *); //#28 +70 .rdata:007963a4
    void    (__thiscall * Function_0029)(void *); //#29 +74 .rdata:007963a8
    void    (__thiscall * Function_0030)(void *); //#30 +78 .rdata:007963ac
    void    (__thiscall * Function_0031)(void *); //#31 +7c .rdata:007963b0
    void    (__thiscall * Function_0032)(void *); //#32 +80 .rdata:007963b4
    void    (__thiscall * Function_0033)(void *); //#33 +84 .rdata:007963b8
    void    (__thiscall * Function_0034)(void *); //#34 +88 .rdata:007963bc
    void    (__thiscall * Function_0035)(void *); //#35 +8c .rdata:007963c0
    void    (__thiscall * Function_0036)(void *); //#36 +90 .rdata:007963c4
    void    (__thiscall * Function_0037)(void *); //#37 +94 .rdata:007963c8
    void    (__thiscall * Function_0038)(void *); //#38 +98 .rdata:007963cc
    void    (__thiscall * Function_0039)(void *); //#39 +9c .rdata:007963d0
    void    (__thiscall * Function_0040)(void *); //#40 +a0 .rdata:007963d4
    void    (__thiscall * Function_0041)(void *); //#41 +a4 .rdata:007963d8
    void    (__thiscall * Function_0042)(void *); //#42 +a8 .rdata:007963dc
    void    (__thiscall * Function_0043)(void *); //#43 +ac .rdata:007963e0
    void    (__thiscall * Function_0044)(void *); //#44 +b0 .rdata:007963e4
    void    (__thiscall * Function_0045)(void *); //#45 +b4 .rdata:007963e8
    void    (__thiscall * Function_0046)(void *); //#46 +b8 .rdata:007963ec
    void    (__thiscall * Function_0047)(void *); //#47 +bc .rdata:007963f0
    void    (__thiscall * Function_0048)(void *); //#48 +c0 .rdata:007963f4
    void    (__thiscall * Function_0049)(void *); //#49 +c4 .rdata:007963f8
    void    (__thiscall * Function_0050)(void *); //#50 +c8 .rdata:007963fc
    void    (__thiscall * Function_0051)(void *); //#51 +cc .rdata:00796400
    void    (__thiscall * Function_0052)(void *); //#52 +d0 .rdata:00796404
    void    (__thiscall * Function_0053)(void *); //#53 +d4 .rdata:00796408
    void    (__thiscall * Function_0054)(void *); //#54 +d8 .rdata:0079640c
    void    (__thiscall * Function_0055)(void *); //#55 +dc .rdata:00796410
    void    (__thiscall * Function_0056)(void *); //#56 +e0 .rdata:00796414
    void    (__thiscall * Function_0057)(void *); //#57 +e4 .rdata:00796418
    void    (__thiscall * Function_0058)(void *); //#58 +e8 .rdata:0079641c
    void    (__thiscall * Function_0059)(void *); //#59 +ec .rdata:00796420
    void    (__thiscall * Function_0060)(void *); //#60 +f0 .rdata:00796424
    void    (__thiscall * Function_0061)(void *); //#61 +f4 .rdata:00796428
    void    (__thiscall * Function_0062)(void *); //#62 +f8 .rdata:0079642c
    void    (__thiscall * Function_0063)(void *); //#63 +fc .rdata:00796430
    void    (__thiscall * find_event)(void *, const char* name); //Glacier::ZEventBase* FindEvent(const char* name); //#64 +100 .rdata:00796434
    void    (__thiscall * Function_0065)(void *); //#65 +104 .rdata:00796438
    void    (__thiscall * Function_0066)(void *); //#66 +108 .rdata:0079643c
    void    (__thiscall * Function_0067)(void *); //#67 +10c .rdata:00796440
    void    (__thiscall * Function_0068)(void *); //#68 +110 .rdata:00796444
    void    (__thiscall * Function_0069)(void *); //#69 +114 .rdata:00796448
    void    (__thiscall * Function_0070)(void *); //#70 +118 .rdata:0079644c
    void    (__thiscall * Function_0071)(void *); //#71 +11c .rdata:00796450
    void    (__thiscall * sendEvent)(void *, int, int); // (uintptr_t ev, int unk0, int unk1); //#72 +120 .rdata:00796454
    void    (__thiscall * Function_0073)(void *); //#73 +124 .rdata:00796458
    void    (__thiscall * Function_0074)(void *); //#74 +128 .rdata:0079645c
    void    (__thiscall * Function_0075)(void *); //#75 +12c .rdata:00796460
    void    (__thiscall * Function_0076)(void *); //#76 +130 .rdata:00796464
    void    (__thiscall * Function_0077)(void *); //#77 +134 .rdata:00796468
    void    (__thiscall * Function_0078)(void *); //#78 +138 .rdata:0079646c
    void    (__thiscall * Function_0079)(void *); //#79 +13c .rdata:00796470
    void    (__thiscall * Function_0080)(void *); //#80 +140 .rdata:00796474
    void    (__thiscall * Function_0081)(void *); //#81 +144 .rdata:00796478
    void    (__thiscall * Function_0082)(void *); //#82 +148 .rdata:0079647c
    void    (__thiscall * Function_0083)(void *); //#83 +14c .rdata:00796480
    void    (__thiscall * Function_0084)(void *); //#84 +150 .rdata:00796484
    void    (__thiscall * Function_0085)(void *); //#85 +154 .rdata:00796488
    void    (__thiscall * Function_0086)(void *); //#86 +158 .rdata:0079648c
    void    (__thiscall * processAI)(void *);     //#87 +15c .rdata:00796490
    void    (__thiscall * Function_0088)(void *); //#88 +160 .rdata:00796494
    void    (__thiscall * dropAnimation)(void *, int, int); // (int, int); //#89 +164 .rdata:00796498
    void    (__thiscall * Function_0090)(void *); //#90 +168 .rdata:0079649c
    void    (__thiscall * Function_0091)(void *); //#91 +16c .rdata:007964a0
    void    (__thiscall * Function_0092)(void *); //#92 +170 .rdata:007964a4
    void    (__thiscall * Function_0093)(void *); //#93 +174 .rdata:007964a8
    void    (__thiscall * Function_0094)(void *); //#94 +178 .rdata:007964ac
    void    (__thiscall * Function_0095)(void *); //#95 +17c .rdata:007964b0
    void    (__thiscall * Function_0096)(void *); //#96 +180 .rdata:007964b4
    void    (__thiscall * Function_0097)(void *); //#97 +184 .rdata:007964b8
    void    (__thiscall * Function_0098)(void *); //#98 +188 .rdata:007964bc
    void    (__thiscall * Function_0099)(void *); //#99 +18c .rdata:007964c0
    void    (__thiscall * Function_0100)(void *); //#100 +190 .rdata:007964c4
    void    (__thiscall * Function_0101)(void *); //#101 +194 .rdata:007964c8
    void    (__thiscall * Function_0102)(void *); //#102 +198 .rdata:007964cc
    void    (__thiscall * Function_0103)(void *); //#103 +19c .rdata:007964d0
    void    (__thiscall * Function_0104)(void *); //#104 +1a0 .rdata:007964d4
    void    (__thiscall * Function_0105)(void *); //#105 +1a4 .rdata:007964d8
    void    (__thiscall * Function_0106)(void *); //#106 +1a8 .rdata:007964dc
    void    (__thiscall * Function_0107)(void *); //#107 +1ac .rdata:007964e0
    void    (__thiscall * Function_0108)(void *); //#108 +1b0 .rdata:007964e4
    void    (__thiscall * Function_0109)(void *); //#109 +1b4 .rdata:007964e8
    void    (__thiscall * Function_0110)(void *); //#110 +1b8 .rdata:007964ec
    void    (__thiscall * Function_0111)(void *); //#111 +1bc .rdata:007964f0
    void    (__thiscall * Function_0112)(void *); //#112 +1c0 .rdata:007964f4
    void    (__thiscall * Function_0113)(void *); //#113 +1c4 .rdata:007964f8
    void    (__thiscall * Function_0114)(void *); //#114 +1c8 .rdata:007964fc
    void    (__thiscall * Function_0115)(void *); //#115 +1cc .rdata:00796500
    void    (__thiscall * Function_0116)(void *); //#116 +1d0 .rdata:00796504
    void    (__thiscall * Function_0117)(void *); //#117 +1d4 .rdata:00796508
    void    (__thiscall * Function_0118)(void *); //#118 +1d8 .rdata:0079650c
    void    (__thiscall * Function_0119)(void *); //#119 +1dc .rdata:00796510
    void    (__thiscall * Function_0120)(void *); //#120 +1e0 .rdata:00796514
    void    (__thiscall * Function_0121)(void *); //#121 +1e4 .rdata:00796518
    void    (__thiscall * Function_0122)(void *); //#122 +1e8 .rdata:0079651c
    void    (__thiscall * Function_0123)(void *); //#123 +1ec .rdata:00796520
    void    (__thiscall * Function_0124)(void *); //#124 +1f0 .rdata:00796524
    void    (__thiscall * anim)(void *, void *, int, float, float, float); // Function_0125(Glacier::ZAnimationInfo* _anim, int _flag, float a0, float a1, float a2); //#125 +1f4 .rdata:00796528
    void    (__thiscall * setAnimation)(void *, int);  // Glacier::ZAnimationInfo** setAnimation(Glacier::ZAnimationInfo* animation, int unknown0 = 1); //#126 +1f8 .rdata:0079652c
    void    (__thiscall * Function_0127)(void *); //#127 +1fc .rdata:00796530
    void    (__thiscall * Function_0128)(void *); //#128 +200 .rdata:00796534
    void    (__thiscall * Function_0129)(void *); //#129 +204 .rdata:00796538
    void    (__thiscall * Function_0130)(void *); //#130 +208 .rdata:0079653c
    void    (__thiscall * Function_0131)(void *); //#131 +20c .rdata:00796540
    void    (__thiscall * Function_0132)(void *); //#132 +210 .rdata:00796544
    void    (__thiscall * Function_0133)(void *); //#133 +214 .rdata:00796548
    void    (__thiscall * Function_0134)(void *); //#134 +218 .rdata:0079654c
    void    (__thiscall * Function_0135)(void *); //#135 +21c .rdata:00796550
    void    (__thiscall * Function_0136)(void *); //#136 +220 .rdata:00796554
    void    (__thiscall * Function_0137)(void *); //#137 +224 .rdata:00796558
    void    (__thiscall * Function_0138)(void *); //#138 +228 .rdata:0079655c
    void    (__thiscall * Function_0139)(void *); //#139 +22c .rdata:00796560
    void    (__thiscall * Function_0140)(void *); //#140 +230 .rdata:00796564
    void    (__thiscall * Function_0141)(void *); //#141 +234 .rdata:00796568
    void    (__thiscall * Function_0142)(void *); //#142 +238 .rdata:0079656c
    void    (__thiscall * Function_0143)(void *); //#143 +23c .rdata:00796570
    void    (__thiscall * Function_0144)(void *); //#144 +240 .rdata:00796574
    void    (__thiscall * Function_0145)(void *); //#145 +244 .rdata:00796578
    void    (__thiscall * Function_0146)(void *); //#146 +248 .rdata:0079657c
    void    (__thiscall * Function_0147)(void *); //#147 +24c .rdata:00796580
    void    (__thiscall * Function_0148)(void *); //#148 +250 .rdata:00796584
    void    (__thiscall * Function_0149)(void *); //#149 +254 .rdata:00796588
    void    (__thiscall * Function_0150)(void *); //#150 +258 .rdata:0079658c
    void    (__thiscall * Function_0151)(void *); //#151 +25c .rdata:00796590
    void    (__thiscall * Function_0152)(void *); //#152 +260 .rdata:00796594
    void    (__thiscall * Function_0153)(void *); //#153 +264 .rdata:00796598
    void    (__thiscall * Function_0154)(void *); //#154 +268 .rdata:0079659c
    void    (__thiscall * Function_0155)(void *); //#155 +26c .rdata:007965a0
    void    (__thiscall * Function_0156)(void *); //#156 +270 .rdata:007965a4
    void    (__thiscall * Function_0157)(void *); //#157 +274 .rdata:007965a8
    void    (__thiscall * Function_0158)(void *); //#158 +278 .rdata:007965ac
    void    (__thiscall * Function_0159)(void *); //#159 +27c .rdata:007965b0
    void    (__thiscall * Function_0160)(void *); //#160 +280 .rdata:007965b4
    void    (__thiscall * Function_0161)(void *); //#161 +284 .rdata:007965b8
    void    (__thiscall * Function_0162)(void *); //#162 +288 .rdata:007965bc
    void    (__thiscall * Function_0163)(void *); //#163 +28c .rdata:007965c0
    void    (__thiscall * Function_0164)(void *); //#164 +290 .rdata:007965c4
    void    (__thiscall * Function_0165)(void *); //#165 +294 .rdata:007965c8
    void    (__thiscall * Function_0166)(void *); //#166 +298 .rdata:007965cc
    void    (__thiscall * Function_0167)(void *); //#167 +29c .rdata:007965d0
    void    (__thiscall * Function_0168)(void *); //#168 +2a0 .rdata:007965d4
    void    (__thiscall * Function_0169)(void *); //#169 +2a4 .rdata:007965d8
    void    (__thiscall * Function_0170)(void *); //#170 +2a8 .rdata:007965dc
    void    (__thiscall * Function_0171)(void *); //#171 +2ac .rdata:007965e0
    void    (__thiscall * Function_0172)(void *); //#172 +2b0 .rdata:007965e4
    void    (__thiscall * Function_0173)(void *); //#173 +2b4 .rdata:007965e8
    void    (__thiscall * Function_0174)(void *); //#174 +2b8 .rdata:007965ec
    void    (__thiscall * Function_0175)(void *); //#175 +2bc .rdata:007965f0
    void    (__thiscall * Function_0176)(void *); //#176 +2c0 .rdata:007965f4
    void    (__thiscall * Function_0177)(void *); //#177 +2c4 .rdata:007965f8
    void    (__thiscall * Function_0178)(void *); //#178 +2c8 .rdata:007965fc
    void    (__thiscall * Function_0179)(void *); //#179 +2cc .rdata:00796600
    void    (__thiscall * Function_0180)(void *); //#180 +2d0 .rdata:00796604
    void    (__thiscall * Function_0181)(void *); //#181 +2d4 .rdata:00796608
    void    (__thiscall * Function_0182)(void *); //#182 +2d8 .rdata:0079660c
    void    (__thiscall * Function_0183)(void *); //#183 +2dc .rdata:00796610
    void    (__thiscall * Function_0184)(void *); //#184 +2e0 .rdata:00796614
    void    (__thiscall * Function_0185)(void *); //#185 +2e4 .rdata:00796618
    void    (__thiscall * Function_0186)(void *); //#186 +2e8 .rdata:0079661c
    void    (__thiscall * Function_0187)(void *); //#187 +2ec .rdata:00796620
    int     (__thiscall * Function_0188)(void *); //#188 +2f0 .rdata:00796624 {desc=Get +B40 field from thisptr)
    int     (__thiscall * Function_0189)(void *); //#189 +2f4 .rdata:00796628
    int     (__thiscall * Function_0190)(void *); //#190 +2f8 .rdata:0079662c
    void    (__thiscall * Function_0191)(void *); //#191 +2fc .rdata:00796630
    void    (__thiscall * Function_0192)(void *); // (int _a0, int _a1, int _a2); //#192 +300 .rdata:00796634 (possible rotate actor or navigate)
    void    (__thiscall * Function_0193)(void *); //#193 +304 .rdata:00796638 {load anim cache}
    void    (__thiscall * Function_0194)(void *); //#194 +308 .rdata:0079663c
    void    (__thiscall * Function_0195)(void *); //#195 +30c .rdata:00796640
    void    (__thiscall * Function_0196)(void *); //#196 +310 .rdata:00796644
    void    (__thiscall * Function_0197)(void *); //#197 +314 .rdata:00796648
    void    (__thiscall * Function_0198)(void *); //#198 +318 .rdata:0079664c
    void    (__thiscall * Function_0199)(void *); //#199 +31c .rdata:00796650
    void    (__thiscall * Function_0200)(void *); //#200 +320 .rdata:00796654
    void    (__thiscall * Function_0201)(void *); //#201 +324 .rdata:00796658
    void    (__thiscall * Function_0202)(void *); //#202 +328 .rdata:0079665c
    void    (__thiscall * Function_0203)(void *); //#203 +32c .rdata:00796660
    void    (__thiscall * Function_0204)(void *); //#204 +330 .rdata:00796664
    void    (__thiscall * Function_0205)(void *); //#205 +334 .rdata:00796668
    void    (__thiscall * Function_0206)(void *); //#206 +338 .rdata:0079666c
    void    (__thiscall * Function_0207)(void *); //#207 +33c .rdata:00796670
    void    (__thiscall * Function_0208)(void *); //#208 +340 .rdata:00796674
    void    (__thiscall * Function_0209)(void *); //#209 +344 .rdata:00796678
    void    (__thiscall * Function_0210)(void *); //#210 +348 .rdata:0079667c
    void    (__thiscall * Function_0211)(void *); //#211 +34c .rdata:00796680
    void    (__thiscall * Function_0212)(void *); //#212 +350 .rdata:00796684
    void    (__thiscall * Function_0213)(void *); //#213 +354 .rdata:00796688
    void    (__thiscall * Function_0214)(void *); //#214 +358 .rdata:0079668c
    void    (__thiscall * Function_0215)(void *); //#215 +35c .rdata:00796690
    void    (__thiscall * Function_0216)(void *); //#216 +360 .rdata:00796694
    void    (__thiscall * Function_0217)(void *); //#217 +364 .rdata:00796698
    void    (__thiscall * Function_0218)(void *); //#218 +368 .rdata:0079669c
    void    (__thiscall * Function_0219)(void *); //#219 +36c .rdata:007966a0
    void    (__thiscall * Function_0220)(void *); //#220 +370 .rdata:007966a4
    void    (__thiscall * Function_0221)(void *); //#221 +374 .rdata:007966a8
    void    (__thiscall * Function_0222)(void *); //#222 +378 .rdata:007966ac
    void    (__thiscall * Function_0223)(void *); //#223 +37c .rdata:007966b0
    void    (__thiscall * Function_0224)(void *); //#224 +380 .rdata:007966b4
    void    (__thiscall * Function_0225)(void *); //#225 +384 .rdata:007966b8
    void    (__thiscall * Function_0226)(void *); //#226 +388 .rdata:007966bc
    void    (__thiscall * Function_0227)(void *); //#227 +38c .rdata:007966c0
    void    (__thiscall * getActionByEnum)(void *, int); // ZLnkAction* getActionByEnum(UnknownEnum a0); //#228 +390 .rdata:007966c4
    void    (__thiscall * Function_0229)(void *); //#229 +394 .rdata:007966c8
    void    (__thiscall * Function_0230)(void *); //#230 +398 .rdata:007966cc
    void    (__thiscall * Function_0231)(void *); //#231 +39c .rdata:007966d0
    void    (__thiscall * Function_0232)(void *); //#232 +3a0 .rdata:007966d4
    void    (__thiscall * Function_0233)(void *); //#233 +3a4 .rdata:007966d8
    void    (__thiscall * Function_0234)(void *); //#234 +3a8 .rdata:007966dc
    void    (__thiscall * Function_0235)(void *); //#235 +3ac .rdata:007966e0
    void    (__thiscall * Function_0236)(void *); //#236 +3b0 .rdata:007966e4
    void    (__thiscall * Function_0237)(void *); //#237 +3b4 .rdata:007966e8
    void    (__thiscall * Function_0238)(void *); //#238 +3b8 .rdata:007966ec
    void    (__thiscall * Function_0239)(void *, int); // (int _unk0); //#239 +3bc .rdata:007966f0
    void    (__thiscall * Function_0240)(void *); //#240 +3c0 .rdata:007966f4
    void    (__thiscall * Function_0241)(void *, int); // (int _possibleItemId); //#241 +3c4 .rdata:007966f8
    void    (__thiscall * Function_0242)(void *); //#242 +3c8 .rdata:007966fc
    void    (__thiscall * Function_0243)(void *); //#243 +3cc .rdata:00796700
    void    (__thiscall * Function_0244)(void *); //#244 +3d0 .rdata:00796704
    void    (__thiscall * Function_0245)(void *); //#245 +3d4 .rdata:00796708
    void    (__thiscall * Function_0246)(void *); //#246 +3d8 .rdata:0079670c
    int     (__thiscall * Function_0247)(void *); //#247 +3dc .rdata:00796710
    void    (__thiscall * Function_0248)(void *); //#248 +3e0 .rdata:00796714
    void    (__thiscall * Function_0249)(void *); //#249 +3e4 .rdata:00796718
    void    (__thiscall * Function_0250)(void *); //#250 +3e8 .rdata:0079671c
    void    (__thiscall * Function_0251)(void *); //#251 +3ec .rdata:00796720
    void    (__thiscall * Function_0252)(void *); //#252 +3f0 .rdata:00796724
    void    (__thiscall * Function_0253)(void *); //#253 +3f4 .rdata:00796728
    void    (__thiscall * Function_0254)(void *); //#254 +3f8 .rdata:0079672c
    void    (__thiscall * Function_0255)(void *); //#255 +3fc .rdata:00796730
    void    (__thiscall * Function_0256)(void *); //#256 +400 .rdata:00796734
    void    (__thiscall * Function_0257)(void *); //#257 +404 .rdata:00796738
    void    (__thiscall * Function_0258)(void *); //#258 +408 .rdata:0079673c
    void    (__thiscall * Function_0259)(void *); //#259 +40c .rdata:00796740
    void    (__thiscall * Function_0260)(void *, int, int); // (UnknownEnum1 _a0, int _itemID); //#260 +410 .rdata:00796744
    char*   (__thiscall * Function_0261)(void *); //#261 +414 .rdata:00796748
    void    (__thiscall * Function_0262)(void *); //#262 +418 .rdata:0079674c
    void    (__thiscall * Function_0263)(void *); //#263 +41c .rdata:00796750
    void    (__thiscall * Function_0264)(void *); //#264 +420 .rdata:00796754
    void    (__thiscall * Function_0265)(void *); //#265 +424 .rdata:00796758
    void    (__thiscall * Function_0266)(void *); //#266 +428 .rdata:0079675c
    void    (__thiscall * Function_0267)(void *); //#267 +42c .rdata:00796760
    void    (__thiscall * Function_0268)(void *); //#268 +430 .rdata:00796764
    void    (__thiscall * Function_0269)(void *); //#269 +434 .rdata:00796768
    void    (__thiscall * Function_0270)(void *); //#270 +438 .rdata:0079676c
    void    (__thiscall * Function_0271)(void *); //#271 +43c .rdata:00796770
    void    (__thiscall * Function_0272)(void *); //#272 +440 .rdata:00796774
    int     (__thiscall * OnlyVerticalAim)(void *); //#273 +444 .rdata:00796778 { always false }
    void    (__thiscall * GetAimAnim)(void *, void **, int*); //(Glacier::Animation::Header** results, uint32_t& count); //#274 +448 .rdata:0079677c
    void    (__thiscall * GetPoseEffects)(void *, float*, unsigned short*); //(float* ,unsigned short*); //#275 +44c .rdata:00796780 { BAD ASSEMBLY! }
    int     (__thiscall * SetHandTarget)(void *, int, void *, float); //(int unknownIndex, Glacier::Vector3*, float); //#276 +450 .rdata:00796784
    void    (__thiscall * DontAnimateAttachers)(void *); //#277 +454 .rdata:00796788 { DO NOT NOTHING }
    void    (__thiscall * RemoveLHandIKTarget)(void *, float, void *); //(float, void* callback); //#278 +458 .rdata:0079678c
    void    (__thiscall * RemoveRHandIKTarget)(void *, float, void *); //(float, void* callback); //#279 +45c .rdata:00796790
    void    (__thiscall * UpdateAimTarget)(void *); //#280 +460 .rdata:00796794
    int     (__thiscall * SetAimTarget)(void *, int, void *, float, void *, int, int, int, int); //(uint32_t, Glacier::Vector3*, float, void* callback, int, int, int, int); //#281 +464 .rdata:00796798 (called by sub_6A6750)
    void    (__thiscall * SetAimTarget2)(void *); // Do not use this function!; //#282 +468 .rdata:0079679c
    void    (__thiscall * RemoveAimTarget)(void *, float, void*); //#283 +46c .rdata:007967a0
    int     (__thiscall * FreezeAimTarget)(void *); //#284 +470 .rdata:007967a4
    void    (__thiscall * DisableAim)(void *); //#285 +474 .rdata:007967a8
    void    (__thiscall * EnableAim)(void *); //#286 +478 .rdata:007967ac
    int     (__thiscall * GetAimTarget)(void *); //#287 +47c .rdata:007967b0
    int     (__thiscall * GetAimTarget2)(void *, uint32_t*); //#288 +480 .rdata:007967b4
    int     (__thiscall * GetAimTarget3)(void *, void *); // (Glacier::Vector3*); //#289 +484 .rdata:007967b8
    float   (__thiscall * GetDrawWeaponSpeed)(void *); //#290 +488 .rdata:007967bc
    int     (__thiscall * IsAiming)(void *); //#291 +48c .rdata:007967c0
    void    (__thiscall * SetAimAnimPrc)(void *, float, float, float); //#292 +490 .rdata:007967c4 { DO NOTHING I GUESS }
    void    (__thiscall * FireShotNotify)(void *); //#293 +494 .rdata:007967c8
    void    (__thiscall * SetHitAnimation)(void *, const char*); //#294 +498 .rdata:007967cc
    void    (__thiscall * SetHitAnimHandle)(void *, int* handle); //#295 +49c .rdata:007967d0
    void    (__thiscall * UseItem)(void *, void* zitem, int); //#296 +4a0 .rdata:007967d4
    void    (__thiscall * DropItem)(void *, void* zitem); //#297 +4a4 .rdata:007967d8
    void    (__thiscall * PickupItem)(void *, void* zitem); //#298 +4a8 .rdata:007967dc
    void    (__thiscall * Reload)(void *, void* zitem); //#299 +4ac .rdata:007967e0
    void    (__thiscall * Chamber)(void *, void* zitem); //#300 +4b0 .rdata:007967e4
    void    (__thiscall * PerformDrop)(void *, void* zitem, int  doPhysicsBody, int  a3); //#301 +4b4 .rdata:007967e8
    void*   (__thiscall * GetRHand)(void *); //#302 +4b8 .rdata:007967ec
    void*   (__thiscall * GetLHand)(void *); //#303 +4bc .rdata:007967f0
    void*   (__thiscall * GetLHandItem)(void *); //#304 +4c0 .rdata:007967f4
    void*   (__thiscall * GetRHandItem)(void *); //#305 +4c4 .rdata:007967f8
    void*   (__thiscall * GetLHandWeapon)(void *); //#306 +4c8 .rdata:007967fc
    void*   (__thiscall * GetRHandWeapon)(void *); //#307 +4cc .rdata:00796800
    void*   (__thiscall * GetRHandItemType)(void *); //#308 +4d0 .rdata:00796804
    void*   (__thiscall * GetLHandItemType)(void *); //#309 +4d4 .rdata:00796808
    void    (__thiscall * SetRHandItemState)(void *, int); // (int itemState); //#310 +4d8 .rdata:0079680c
    void    (__thiscall * SetLHandItemState)(void *, int); // (int itemState); //#311 +4dc .rdata:00796810
    void    (__thiscall * AttachItemToHand)(void *, void* hand, int itemid); //(Glacier::ZIKHAND* hand, uint32_t itemId); //#312 +4e0 .rdata:00796814
    int     (__thiscall * AttachRHandItem)(void *, int itemid); //(uint32_t itemID); //#313 +4e4 .rdata:00796818
    int     (__thiscall * AttachLHandItem)(void *, int itemid); //(uint32_t itemID); //#314 +4e8 .rdata:0079681c
    void    (__thiscall * GetNearItems)(void *); //#315 +4ec .rdata:00796820 {similar to next}
    void    (__thiscall * GetNearItems2)(void *); //#316 +4f0 .rdata:00796824 {similar to prev}
    void    (__thiscall * SetDialog)(void *, int); //#317 +4f4 .rdata:00796828
    int     (__thiscall * GetDialog)(void *); //#318 +4f8 .rdata:0079682c
    void*   (__thiscall * DialogListen)(void *, int variant); //#319 +4fc .rdata:00796830 {variant between 0 and 1}
    void*   (__thiscall * DialogTalk)(void *, int variant); //#320 +500 .rdata:00796834 {variant between 0 and 1}
    void    (__thiscall * ForceRHandItem)(void *, void * zitem, int); //#321 +504 .rdata:00796838
    void    (__thiscall * ForceLHandItem)(void *, void *zitem, int); //#322 +508 .rdata:0079683c {second int  not used I guess}
    void    (__thiscall * Function_0323)(void *); //#323 +50c .rdata:00796840
    void    (__thiscall * DestroyRHandItem)(void *); //#324 +510 .rdata:00796844
    void    (__thiscall * DestroyLHandItem)(void *); //#325 +514 .rdata:00796848
    int     (__thiscall * EmptyHands)(void *); //#326 +518 .rdata:0079684c
    void    (__thiscall * SetAmmoFor)(void *, void* zitemweaopon, int); //#327 +51c .rdata:00796850 (do nothing)
    int     (__thiscall * GetAmmoFor)(void *, void* ZItemWeapon); //#328 +520 .rdata:00796854 {always 999}
    void    (__thiscall * SetLHandIKTarget)(void *, const float*, const float*, float, void* callback); //#329 +524 .rdata:00796858
    void    (__thiscall * SetRHandIKTarget)(void *, const float*, const float*, float, void* callback); //#330 +528 .rdata:0079685c
    void    (__thiscall * UpdateItemActions)(void *); //#331 +52c .rdata:00796860
    void    (__thiscall * CallBackItemAction)(void *); //#332 +530 .rdata:00796864
    int     (__thiscall * GetNearItems3)(void *); //#333 +534 .rdata:00796868
    void    (__thiscall * PlaySpeech)(void *, uint32_t, int, int ); //#334 +538 .rdata:0079686c
    void    (__thiscall * PlayFootStep)(void *, int e_foot_side); //#335 +53c .rdata:00796870
    int     (__thiscall * IsFirstPersonCamera)(void *); //#336 +540 .rdata:00796874
    float   (__thiscall * GetCombatStrength)(void *); //#337 +544 .rdata:00796878
    void    (__thiscall * SetActorRootTM)(void *, const void* vec3_a, const void* vec3_b); //#338 +548 .rdata:0079687c
    void    (__thiscall * SetActorPosDir)(void *,const void* vec3_a, const void* vec3_b); //#339 +54c .rdata:00796880
    void*   (__thiscall * GetActorRootTM)(void *, const float*, const float*); //#340 +550 .rdata:00796884
    void    (__thiscall * GetActorWorldPosition)(void *, void* vec3); //#341 +554 .rdata:00796888 {possible setPosition!!!}
    void    (__thiscall * SetActorWorldPosition)(void *, void* vec3); //#342 +558 .rdata:0079688c
    int     (__thiscall * CanPlayAnimSegment)(void *, void* header, float, float, const float*, const float*, int , float, float); //#343 +55c .rdata:00796890
    int     (__thiscall * IsUnconscious)(void *); //#344 +560 .rdata:00796894
    int     (__thiscall * IsAwake)(void *); //#345 +564 .rdata:00796898 {possible isAlive}
    int     (__thiscall * IsSleeping)(void *); //#346 +568 .rdata:0079689c
    void    (__thiscall * SetHero)(void *, uint8_t); //#347 +56c .rdata:007968a0
    int     (__thiscall * SetActorState)(void *, int status); //#348 +570 .rdata:007968a4
    void    (__thiscall * OnViewEnter)(void *); //#349 +574 .rdata:007968a8
    void    (__thiscall * OnViewLeave)(void *); //#350 +578 .rdata:007968ac
    void*   (__thiscall * GetPathFinder4)(void *); //#351 +57c .rdata:007968b0 (return ZEngineDataBase + 0x14)
    int     (__thiscall * EnablePathFinder)(void *, int  _a0); //#352 +580 .rdata:007968b4
    void    (__thiscall * SetStopDistance)(void *, float); //#353 +584 .rdata:007968b8
    void    (__thiscall * SetEndDir)(void *, void* vec3); //#354 +588 .rdata:007968bc (it works with coordinates but not world coordinates [-1.0; 1.0])
    void*   (__thiscall * GetEndDir)(void *); //#355 +58c .rdata:007968c0
    void    (__thiscall * MoveToPosition)(void *, const void* vec3_a, const void* vec3_b); //#356 +590 .rdata:007968c4
    void    (__thiscall * SlideToPosition)(void *, const void* vec3_a, const void* vec3_b); //#357 +594 .rdata:007968c8
    void    (__thiscall * SetPathNotify)(void *, float); //#358 +598 .rdata:007968cc
    void    (__thiscall * SetPathNotifySyncToCycle)(void *, int arg); //#359 +59c .rdata:007968d0
    void    (__thiscall * SetEndAction)(void *, int arg); //#360 +5a0 .rdata:007968d4
    void    (__thiscall * RemovePath)(void *, uint8_t, void* PATH_CANCEL_REASONS, int); //#361 +5a4 .rdata:007968d8
    void    (__thiscall * SendPathDone)(void *, int); //#362 +5a8 .rdata:007968dc
    void*   (__thiscall * GetMoveFromPos)(void *, const void* vec3); //#363 +5ac .rdata:007968e0
    void*   (__thiscall * FindNextPathBlocker)(void *); //#364 +5b0 .rdata:007968e4
    int     (__thiscall * SetShootIntoGround)(void *, int arg); //#365 +5b4 .rdata:007968e8
    int     (__thiscall * SetShootIntoGroundInFullbody)(void *, int _a0); //#366 +5b8 .rdata:007968ec
    int     (__thiscall * SetStayInsidePath)(void *, int _a0); //#367 +5bc .rdata:007968f0
    void    (__thiscall * ShootIntoGround)(void *, float*, int, int); //#368 +5c0 .rdata:007968f4
    void    (__thiscall * ShootIntoGroundRegularly)(void *, float*, int, int, float); //#369 +5c4 .rdata:007968f8
    float   (__thiscall * SetMoveSpeedMultiplier)(void *, float speedMul); //#370 +5c8 .rdata:007968fc {set 5B0 value}
    void    (__thiscall * SetPathFinderEnabled)(void *, int); //#371 +5cc .rdata:00796900
    void    (__thiscall * OnPathRequest)(void *, uint32_t); //#372 +5d0 .rdata:00796904
    void    (__thiscall * OnPathFinished)(void *, uint32_t); //#373 +5d4 .rdata:00796908 {possible reset actor state}
    void    (__thiscall * OnPathCanceled)(void *, void* PATH_CANCEL_ERRORS); //#374 +5d8 .rdata:0079690c
    void    (__thiscall * OnPathCanceledLockedDoor)(void *, uint32_t); //#375 +5dc .rdata:00796910
    void    (__thiscall * OnPathError)(void *, void* PATH_ERRORS); //#376 +5e0 .rdata:00796914
    int     (__thiscall * OnPathNotify)(void *); //#377 +5e4 .rdata:00796918
    void    (__thiscall * OnNewPath)(void *); //#378 +5e8 .rdata:0079691c
    void    (__thiscall * OnSound)(void *, void* rftab); //#379 +5ec .rdata:00796920
    void    (__thiscall * Die)(void *); //#380 +5f0 .rdata:00796924
    void    (__thiscall * DieByForce)(void *, const void* vec3_a, const void* vec3_b, float, int); //#381 +5f4 .rdata:00796928
    int     (__thiscall * Resurrect)(void *); //#382 +5f8 .rdata:0079692c
    int     (__thiscall * Knockout)(void *); //#383 +5fc .rdata:00796930 (possible not but actor not dies here)
    int     (__thiscall * Revive)(void *); //#384 +600 .rdata:00796934 {possible sedate or smth l ths}
    int     (__thiscall * GetKnockedOut)(void *); //#385 +604 .rdata:00796938
    int     (__thiscall * GetActorList)(void *); //#386 +608 .rdata:0079693c
    void    (__thiscall * SetDisableIdleAnimation)(void *, int); //#387 +60c .rdata:00796940
    int     (__thiscall * GetAudibleRoomList)(void *); //#388 +610 .rdata:00796944
    void    (__thiscall * LookAt)(void *, int _a0); //#389 +614 .rdata:00796948
    int     (__thiscall * IsSeeing)(void *); //#390 +618 .rdata:0079694c
    void    (__thiscall * SetSeeing)(void *, int); //#391 +61c .rdata:00796950
    int     (__thiscall * IsVisible)(void *); //#392 +620 .rdata:00796954
    void    (__thiscall * SetVisible)(void *, int); //#393 +624 .rdata:00796958
    void    (__thiscall * WantToLookAt)(void *, void* zgeom, uint8_t); //#394 +628 .rdata:0079695c
    void    (__thiscall * VerifyPlayerVisible)(void *); //#395 +62c .rdata:00796960 (sync suspicious level with ZOSD)
    void    (__thiscall * DeterminePathLookAt)(void *, void* locomotion_info, float *, float *, float *, float *); //#396 +630 .rdata:00796964
    int     (__thiscall * CanLookAt)(void *, void* zgeom); //#397 +634 .rdata:00796968
    int     (__thiscall * IsOnStairs)(void *); //#398 +638 .rdata:0079696c
    void    (__thiscall * UpdatePositionOffScreen)(void *); //#399 +63c .rdata:00796970
    void    (__thiscall * UpdatePosition)(void *); //#400 +640 .rdata:00796974
    int     (__thiscall * GetCurrentUBAnim)(void *, void* zitem_a, void* zitem_b, int*); //#401 +644 .rdata:00796978
    void*   (__thiscall * SetHoldWeaponUBAnim)(void *, void* anim); //#402 +648 .rdata:0079697c
    void    (__thiscall * GetAnimOffset)(void *, const char*); //#403 +64c .rdata:00796980
    void    (__thiscall * GetAnimOffset2)(void *, void* header); //#404 +650 .rdata:00796984
    void*   (__thiscall * GetAnimHeader)(void *, uint32_t); //#405 +654 .rdata:00796988
    void    (__thiscall * Function_0406)(void *); //#406 +658 .rdata:0079698c
    void    (__thiscall * Function_0407)(void *); //#407 +65c .rdata:00796990
    void    (__thiscall * Function_0408)(void *); //#408 +660 .rdata:00796994
    void    (__thiscall * Function_0409)(void *); //#409 +664 .rdata:00796998
    int     (__thiscall * SetWeapon)(void *, int itemID); //#410 +668 .rdata:0079699c, possible giveItem method
    int     (__thiscall * GetWeapon)(void *); //#411 +66c .rdata:007969a0
    void    (__thiscall * SetWeaponTemplate)(void *, uint32_t); //#412 +670 .rdata:007969a4
    int     (__thiscall * GetWeaponTemplate)(void *); //#413 +674 .rdata:007969a8
    int     (__thiscall * FireWeapon)(void *, uint32_t weaponId, int, float, int); //#414 +678 .rdata:007969ac
    void    (__thiscall * Bite)(void *, int, void* vec3_a, void* vec3_b, float, float); //#415 +67c .rdata:007969b0 [Works but need to have a bit in hands]
    void    (__thiscall * Punch)(void *, int); //#416 +680 .rdata:007969b4 [Works but need to determine condition of usage]
    void    (__thiscall * StunGunAttack)(void *); //#417 +684 .rdata:007969b8 [Works, but need to check that actor has stun gun in hands!]
    int     (__thiscall * ThrowKnifeAtRef)(void *, int itemID0, int itemID1); //#418 +688 .rdata:007969bc (knife thrower check, maybe item hooking here)
    void    (__thiscall * ActivateRagdollOrAnim)(void *); //#419 +68c .rdata:007969c0
    void    (__thiscall * ActivateRagdollNextFrame)(void *); //#420 +690 .rdata:007969c4
    void    (__thiscall * InitializeHitpoints)(void *, float); //#421 +694 .rdata:007969c8
    void    (__thiscall * SetHitpoints)(void *, float); //#422 +698 .rdata:007969cc
    int     (__thiscall * GetHitpoints)(void *); //#423 +69c .rdata:007969d0
    void    (__thiscall * TakeDamage)(void *, float); //#424 +6a0 .rdata:007969d4
    float   (__thiscall * GetHealth)(void *); //#425 +6a4 .rdata:007969d8
    float   (__thiscall * GetWeaponStrength)(void *); //#426 +6a8 .rdata:007969dc
    int     (__thiscall * IsDragEnabled)(void *); //#427 +6ac .rdata:007969e0
    void*   (__thiscall * GetItemTemplate)(void *); //#428 +6b0 .rdata:007969e4
    void    (__thiscall * CreateItemFromItemTemplate)(void *, int itemOrItemID); //#429 +6b4 .rdata:007969e8
    void    (__thiscall * ActivateItem)(void *, int itemID, int unk0); //#430 +6b8 .rdata:007969ec | _unk0 allowed only Value7 and Value8
    int     (__thiscall * ConcealItem)(void *, int itemID, int flag0); //#431 +6bc .rdata:007969f0
    void    (__thiscall * EnablePickupClothes)(void *); //#432 +6c0 .rdata:007969f4
    void    (__thiscall * DisablePickupClothes)(void *); //#433 +6c4 .rdata:007969f8
    int     (__thiscall * IsWearingClothes)(void *); //#434 +6c8 .rdata:007969fc
    void    (__thiscall * OnHitmanChangedClothes)(void *); //#435 +6cc .rdata:00796a00
    int     (__thiscall * GetHitmanAs)(void *); //#436 +6d0 .rdata:00796a04
    int     (__thiscall * GetActorProperties)(void *); //#437 +6d4 .rdata:00796a08
    void    (__thiscall * SetScriptUBAnim)(void *, void* header, int); //#438 +6d8 .rdata:00796a0c
    int     (__thiscall * GetDeadBodyFlags)(void *, void* zlnkobj); //#439 +6dc .rdata:00796a10
    void    (__thiscall * StartDrag)(void *, int itemID); //#440 +6e0 .rdata:00796a14
    void    (__thiscall * EndDrag)(void *); //#441 +6e4 .rdata:00796a18
    int     (__thiscall * GetAutoAimTarget)(void *); //#442 +6e8 .rdata:00796a1c
    void    (__thiscall * SetAutoAimTarget)(void *, int value); //#443 +6ec .rdata:00796a20
    void    (__thiscall * StoreUBHoldAnims)(void *); //#444 +6f0 .rdata:00796a24 (loadExtendedAnimations)
    int     (__thiscall * MapUBHoldAnimsToIdx)(void *); //#445 +6f4 .rdata:00796a28
    int     (__thiscall * GetItemAssignedUBAnim)(void *, void* zitem); //#446 +6f8 .rdata:00796a2c
    void    (__thiscall * LoadSave)(void *, void* ISerializerStream); //#447 +6fc .rdata:00796a30 (actor flags, maybe not used by game)
    int     (__thiscall * ActivateRigidBody)(void *, const void * SRigidBodyVelocity); //#448 +700 .rdata:00796a34
} Vtable;

typedef struct _Entity {
    Vtable* vtable;
    int _0x3DC[246];
    float x;
    float y;
    float z;
    int _0x928[336];
    float hp;
} Entity;

typedef struct _EntityObject {
  Entity* entity;
} EntityObject;

typedef struct _EntityList {
  int _0x8[2];
  unsigned int n_entities;
  EntityObject entities[167];
} EntityList;

typedef struct _Coords {
  float x;
  float y;
  float z;
} Coords ;

#ifdef __cplusplus
}
#endif // __cplusplus

#endif // ENTITY_HPP
