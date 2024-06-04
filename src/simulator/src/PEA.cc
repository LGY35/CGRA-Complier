#include "../include/PEA.hh"
#include "../include/GR.hh"





//LSU PEA::LOAD_F0 = LSU(WIRE::load_f0);
//LSU PEA::LOAD_F1 = LSU(WIRE::load_f1);
//LSU PEA::LOAD_F2 = LSU(WIRE::load_f2);
//LSU PEA::LOAD_F3 = LSU(WIRE::load_f3);
//LSU PEA::LOAD_F4 = LSU(WIRE::load_f4);
//LSU PEA::LOAD_F5 = LSU(WIRE::load_f5);
//LSU PEA::LOAD_F6 = LSU(WIRE::load_f6);
//LSU PEA::LOAD_F7 = LSU(WIRE::load_f7);
//LSU PEA::LOAD_W0 = LSU(WIRE::load_w0);
//LSU PEA::LOAD_W1 = LSU(WIRE::load_w1);
//LSU PEA::LOAD_W2 = LSU(WIRE::load_w2);
//LSU PEA::LOAD_W3 = LSU(WIRE::load_w3);
//LSU PEA::LOAD_W4 = LSU(WIRE::load_w4);
//LSU PEA::LOAD_W5 = LSU(WIRE::load_w5);
//LSU PEA::LOAD_W6 = LSU(WIRE::load_w6);
//LSU PEA::LOAD_W7 = LSU(WIRE::load_w7);
//LSU PEA::LOAD_W8 = LSU(WIRE::load_w8);
//LSU PEA::LOAD_W9 = LSU(WIRE::load_w9);
//LSU PEA::LOAD_W10 = LSU(WIRE::load_w10);
//LSU PEA::LOAD_W11 = LSU(WIRE::load_w11);
//LSU PEA::LOAD_W12 = LSU(WIRE::load_w12);
//LSU PEA::LOAD_W13 = LSU(WIRE::load_w13);
//LSU PEA::LOAD_W14 = LSU(WIRE::load_w14);
//LSU PEA::LOAD_W15 = LSU(WIRE::load_w15);
//LSU PEA::LOAD_W16 = LSU(WIRE::load_w16);
//LSU PEA::LOAD_W17 = LSU(WIRE::load_w17);
//LSU PEA::LOAD_W18 = LSU(WIRE::load_w18);
//LSU PEA::LOAD_W19 = LSU(WIRE::load_w19);
//LSU PEA::LOAD_W20 = LSU(WIRE::load_w20);
//LSU PEA::LOAD_W21 = LSU(WIRE::load_w21);
//LSU PEA::LOAD_W22 = LSU(WIRE::load_w22);
//LSU PEA::LOAD_W23 = LSU(WIRE::load_w23);
//LSU PEA::LOAD_W24 = LSU(WIRE::load_w24);
//LSU PEA::LOAD_W25 = LSU(WIRE::load_w25);
//LSU PEA::LOAD_W26 = LSU(WIRE::load_w26);
//LSU PEA::LOAD_W27 = LSU(WIRE::load_w27);
//LSU PEA::LOAD_W28 = LSU(WIRE::load_w28);
//LSU PEA::LOAD_W29 = LSU(WIRE::load_w29);
//LSU PEA::LOAD_W30 = LSU(WIRE::load_w30);
//LSU PEA::LOAD_W31 = LSU(WIRE::load_w31);
//LSU PEA::LOAD_W32 = LSU(WIRE::load_w32);
//LSU PEA::LOAD_W33 = LSU(WIRE::load_w33);
//LSU PEA::LOAD_W34 = LSU(WIRE::load_w34);
//LSU PEA::LOAD_W35 = LSU(WIRE::load_w35);
//LSU PEA::LOAD_W36 = LSU(WIRE::load_w36);
//LSU PEA::LOAD_W37 = LSU(WIRE::load_w37);
//LSU PEA::LOAD_W38 = LSU(WIRE::load_w38);
//LSU PEA::LOAD_W39 = LSU(WIRE::load_w39);
//LSU PEA::LOAD_W40 = LSU(WIRE::load_w40);
//LSU PEA::LOAD_W41 = LSU(WIRE::load_w41);
//LSU PEA::LOAD_W42 = LSU(WIRE::load_w42);
//LSU PEA::LOAD_W43 = LSU(WIRE::load_w43);
//LSU PEA::LOAD_W44 = LSU(WIRE::load_w44);
//LSU PEA::LOAD_W45 = LSU(WIRE::load_w45);
//LSU PEA::LOAD_W46 = LSU(WIRE::load_w46);
//LSU PEA::LOAD_W47 = LSU(WIRE::load_w47);
//LSU PEA::LOAD_W48 = LSU(WIRE::load_w48);
//LSU PEA::LOAD_W49 = LSU(WIRE::load_w49);
//LSU PEA::LOAD_W50 = LSU(WIRE::load_w50);
//LSU PEA::LOAD_W51 = LSU(WIRE::load_w51);
//LSU PEA::LOAD_W52 = LSU(WIRE::load_w52);
//LSU PEA::LOAD_W53 = LSU(WIRE::load_w53);
//LSU PEA::LOAD_W54 = LSU(WIRE::load_w54);
//LSU PEA::LOAD_W55 = LSU(WIRE::load_w55);
//LSU PEA::LOAD_W56 = LSU(WIRE::load_w56);
//LSU PEA::LOAD_W57 = LSU(WIRE::load_w57);
//LSU PEA::LOAD_W58 = LSU(WIRE::load_w58);
//LSU PEA::LOAD_W59 = LSU(WIRE::load_w59);
//LSU PEA::LOAD_W60 = LSU(WIRE::load_w60);
//LSU PEA::LOAD_W61 = LSU(WIRE::load_w61);
//LSU PEA::LOAD_W62 = LSU(WIRE::load_w62);
//LSU PEA::LOAD_W63 = LSU(WIRE::load_w63);
//LSU PEA::STORE_F0 = LSU(WIRE::store_f0);
//LSU PEA::STORE_F1 = LSU(WIRE::store_f1);
//LSU PEA::STORE_F2 = LSU(WIRE::store_f2);
//LSU PEA::STORE_F3 = LSU(WIRE::store_f3);
//LSU PEA::STORE_F4 = LSU(WIRE::store_f4);
//LSU PEA::STORE_F5 = LSU(WIRE::store_f5);
//LSU PEA::STORE_F6 = LSU(WIRE::store_f6);
//LSU PEA::STORE_F7 = LSU(WIRE::store_f7);
void PEA::PEA_setup() {
	
	for (int i = 0; i < PE_SIZE; i++)
	{
		PEA::PEid.push_back(PE(WIRE::PEinterface[i],i));
	}

	/*

	LOAD_F0 = LSU(WIRE::load_f0);
	LOAD_F1 = LSU(WIRE::load_f1);
	LOAD_F2 = LSU(WIRE::load_f2);
	LOAD_F3 = LSU(WIRE::load_f3);
	LOAD_F4 = LSU(WIRE::load_f4);
	LOAD_F5 = LSU(WIRE::load_f5);
	LOAD_F6 = LSU(WIRE::load_f6);
	LOAD_F7 = LSU(WIRE::load_f7);

	LOAD_W0 = LSU(WIRE::load_w0);
	LOAD_W1 = LSU(WIRE::load_w1);
	LOAD_W2 = LSU(WIRE::load_w2);
	LOAD_W3 = LSU(WIRE::load_w3);
	LOAD_W4 = LSU(WIRE::load_w4);
	LOAD_W5 = LSU(WIRE::load_w5);
	LOAD_W6 = LSU(WIRE::load_w6);
	LOAD_W7 = LSU(WIRE::load_w7);
	LOAD_W8 = LSU(WIRE::load_w8);
	LOAD_W9 = LSU(WIRE::load_w9);
	LOAD_W10 = LSU(WIRE::load_w10);
	LOAD_W11 = LSU(WIRE::load_w11);
	LOAD_W12 = LSU(WIRE::load_w12);
	LOAD_W13 = LSU(WIRE::load_w13);
	LOAD_W14 = LSU(WIRE::load_w14);
	LOAD_W15 = LSU(WIRE::load_w15);
	LOAD_W16 = LSU(WIRE::load_w16);
	LOAD_W17 = LSU(WIRE::load_w17);
	LOAD_W18 = LSU(WIRE::load_w18);
	LOAD_W19 = LSU(WIRE::load_w19);
	LOAD_W20 = LSU(WIRE::load_w20);
	LOAD_W21 = LSU(WIRE::load_w21);
	LOAD_W22 = LSU(WIRE::load_w22);
	LOAD_W23 = LSU(WIRE::load_w23);
	LOAD_W24 = LSU(WIRE::load_w24);
	LOAD_W25 = LSU(WIRE::load_w25);
	LOAD_W26 = LSU(WIRE::load_w26);
	LOAD_W27 = LSU(WIRE::load_w27);
	LOAD_W28 = LSU(WIRE::load_w28);
	LOAD_W29 = LSU(WIRE::load_w29);
	LOAD_W30 = LSU(WIRE::load_w30);
	LOAD_W31 = LSU(WIRE::load_w31);
	LOAD_W32 = LSU(WIRE::load_w32);
	LOAD_W33 = LSU(WIRE::load_w33);
	LOAD_W34 = LSU(WIRE::load_w34);
	LOAD_W35 = LSU(WIRE::load_w35);
	LOAD_W36 = LSU(WIRE::load_w36);
	LOAD_W37 = LSU(WIRE::load_w37);
	LOAD_W38 = LSU(WIRE::load_w38);
	LOAD_W39 = LSU(WIRE::load_w39);
	LOAD_W40 = LSU(WIRE::load_w40);
	LOAD_W41 = LSU(WIRE::load_w41);
	LOAD_W42 = LSU(WIRE::load_w42);
	LOAD_W43 = LSU(WIRE::load_w43);
	LOAD_W44 = LSU(WIRE::load_w44);
	LOAD_W45 = LSU(WIRE::load_w45);
	LOAD_W46 = LSU(WIRE::load_w46);
	LOAD_W47 = LSU(WIRE::load_w47);
	LOAD_W48 = LSU(WIRE::load_w48);
	LOAD_W49 = LSU(WIRE::load_w49);
	LOAD_W50 = LSU(WIRE::load_w50);
	LOAD_W51 = LSU(WIRE::load_w51);
	LOAD_W52 = LSU(WIRE::load_w52);
	LOAD_W53 = LSU(WIRE::load_w53);
	LOAD_W54 = LSU(WIRE::load_w54);
	LOAD_W55 = LSU(WIRE::load_w55);
	LOAD_W56 = LSU(WIRE::load_w56);
	LOAD_W57 = LSU(WIRE::load_w57);
	LOAD_W58 = LSU(WIRE::load_w58);
	LOAD_W59 = LSU(WIRE::load_w59);
	LOAD_W60 = LSU(WIRE::load_w60);
	LOAD_W61 = LSU(WIRE::load_w61);
	LOAD_W62 = LSU(WIRE::load_w62);
	LOAD_W63 = LSU(WIRE::load_w63);

	STORE_F0 = LSU(WIRE::store_f0);
	STORE_F1 = LSU(WIRE::store_f1);
	STORE_F2 = LSU(WIRE::store_f2);
	STORE_F3 = LSU(WIRE::store_f3);
	STORE_F4 = LSU(WIRE::store_f4);
	STORE_F5 = LSU(WIRE::store_f5);
	STORE_F6 = LSU(WIRE::store_f6);
	STORE_F7 = LSU(WIRE::store_f7);*/
}
void PEA::PEA_reset() {
	for (int i = 0; i < PE_SIZE; i++)
	{
		PEA::PEid[i].PE_reset();
	}
/*
	LOAD_F0.LSU_reset();
	LOAD_F1.LSU_reset();
	LOAD_F2.LSU_reset();
	LOAD_F3.LSU_reset();
	LOAD_F4.LSU_reset();
	LOAD_F5.LSU_reset();
	LOAD_F6.LSU_reset();
	LOAD_F7.LSU_reset();

	LOAD_W0.LSU_reset();
	LOAD_W1.LSU_reset();
	LOAD_W2.LSU_reset();
	LOAD_W3.LSU_reset();
	LOAD_W4.LSU_reset();
	LOAD_W5.LSU_reset();
	LOAD_W6.LSU_reset();
	LOAD_W7.LSU_reset();
	LOAD_W8.LSU_reset();
	LOAD_W9.LSU_reset();
	LOAD_W10.LSU_reset();
	LOAD_W11.LSU_reset();
	LOAD_W12.LSU_reset();
	LOAD_W13.LSU_reset();
	LOAD_W14.LSU_reset();
	LOAD_W15.LSU_reset();
	LOAD_W16.LSU_reset();
	LOAD_W17.LSU_reset();
	LOAD_W18.LSU_reset();
	LOAD_W19.LSU_reset();
	LOAD_W20.LSU_reset();
	LOAD_W21.LSU_reset();
	LOAD_W22.LSU_reset();
	LOAD_W23.LSU_reset();
	LOAD_W24.LSU_reset();
	LOAD_W25.LSU_reset();
	LOAD_W26.LSU_reset();
	LOAD_W27.LSU_reset();
	LOAD_W28.LSU_reset();
	LOAD_W29.LSU_reset();
	LOAD_W30.LSU_reset();
	LOAD_W31.LSU_reset();
	LOAD_W32.LSU_reset();
	LOAD_W33.LSU_reset();
	LOAD_W34.LSU_reset();
	LOAD_W35.LSU_reset();
	LOAD_W36.LSU_reset();
	LOAD_W37.LSU_reset();
	LOAD_W38.LSU_reset();
	LOAD_W39.LSU_reset();
	LOAD_W40.LSU_reset();
	LOAD_W41.LSU_reset();
	LOAD_W42.LSU_reset();
	LOAD_W43.LSU_reset();
	LOAD_W44.LSU_reset();
	LOAD_W45.LSU_reset();
	LOAD_W46.LSU_reset();
	LOAD_W47.LSU_reset();
	LOAD_W48.LSU_reset();
	LOAD_W49.LSU_reset();
	LOAD_W50.LSU_reset();
	LOAD_W51.LSU_reset();
	LOAD_W52.LSU_reset();
	LOAD_W53.LSU_reset();
	LOAD_W54.LSU_reset();
	LOAD_W55.LSU_reset();
	LOAD_W56.LSU_reset();
	LOAD_W57.LSU_reset();
	LOAD_W58.LSU_reset();
	LOAD_W59.LSU_reset();
	LOAD_W60.LSU_reset();
	LOAD_W61.LSU_reset();
	LOAD_W62.LSU_reset();
	LOAD_W63.LSU_reset();

	STORE_F0.LSU_reset();
	STORE_F1.LSU_reset();
	STORE_F2.LSU_reset();
	STORE_F3.LSU_reset();
	STORE_F4.LSU_reset();
	STORE_F5.LSU_reset();
	STORE_F6.LSU_reset();
	STORE_F7.LSU_reset();*/
    
	WIRE::WIRE_reset();
	return;
}
void PEA::START_SIG_RISING_EDGE(bool* Pea_enable, bool* Lf_enable, bool* Lw_enable, bool* Sf_enable) {
	WIRE::PE_START_IN_0 = Pea_enable[0] ? 1 : 0;
	WIRE::PE_START_IN_1 = Pea_enable[1] ? 1 : 0;
	WIRE::PE_START_IN_2 = Pea_enable[2] ? 1 : 0;
	WIRE::PE_START_IN_3 = Pea_enable[3] ? 1 : 0;
	WIRE::PE_START_IN_4 = Pea_enable[4] ? 1 : 0;
	WIRE::PE_START_IN_5 = Pea_enable[5] ? 1 : 0;
	WIRE::PE_START_IN_6 = Pea_enable[6] ? 1 : 0;
	WIRE::PE_START_IN_7 = Pea_enable[7] ? 1 : 0;
	WIRE::PE_START_IN_8 = Pea_enable[8] ? 1 : 0;
	WIRE::PE_START_IN_9 = Pea_enable[9] ? 1 : 0;
	WIRE::PE_START_IN_10 = Pea_enable[10] ? 1 : 0;
	WIRE::PE_START_IN_11 = Pea_enable[11] ? 1 : 0;
	WIRE::PE_START_IN_12 = Pea_enable[12] ? 1 : 0;
	WIRE::PE_START_IN_13 = Pea_enable[13] ? 1 : 0;
	WIRE::PE_START_IN_14 = Pea_enable[14] ? 1 : 0;
	WIRE::PE_START_IN_15 = Pea_enable[15] ? 1 : 0;
	WIRE::PE_START_IN_16 = Pea_enable[16] ? 1 : 0;
	WIRE::PE_START_IN_17 = Pea_enable[17] ? 1 : 0;
	WIRE::PE_START_IN_18 = Pea_enable[18] ? 1 : 0;
	WIRE::PE_START_IN_19 = Pea_enable[19] ? 1 : 0;
	WIRE::PE_START_IN_20 = Pea_enable[20] ? 1 : 0;
	WIRE::PE_START_IN_21 = Pea_enable[21] ? 1 : 0;
	WIRE::PE_START_IN_22 = Pea_enable[22] ? 1 : 0;
	WIRE::PE_START_IN_23 = Pea_enable[23] ? 1 : 0;
	WIRE::PE_START_IN_24 = Pea_enable[24] ? 1 : 0;
	WIRE::PE_START_IN_25 = Pea_enable[25] ? 1 : 0;
	WIRE::PE_START_IN_26 = Pea_enable[26] ? 1 : 0;
	WIRE::PE_START_IN_27 = Pea_enable[27] ? 1 : 0;
	WIRE::PE_START_IN_28 = Pea_enable[28] ? 1 : 0;
	WIRE::PE_START_IN_29 = Pea_enable[29] ? 1 : 0;
	WIRE::PE_START_IN_30 = Pea_enable[30] ? 1 : 0;
	WIRE::PE_START_IN_31 = Pea_enable[31] ? 1 : 0;
	WIRE::PE_START_IN_32 = Pea_enable[32] ? 1 : 0;
	WIRE::PE_START_IN_33 = Pea_enable[33] ? 1 : 0;
	WIRE::PE_START_IN_34 = Pea_enable[34] ? 1 : 0;
	WIRE::PE_START_IN_35 = Pea_enable[35] ? 1 : 0;
	WIRE::PE_START_IN_36 = Pea_enable[36] ? 1 : 0;
	WIRE::PE_START_IN_37 = Pea_enable[37] ? 1 : 0;
	WIRE::PE_START_IN_38 = Pea_enable[38] ? 1 : 0;
	WIRE::PE_START_IN_39 = Pea_enable[39] ? 1 : 0;
	WIRE::PE_START_IN_40 = Pea_enable[40] ? 1 : 0;
	WIRE::PE_START_IN_41 = Pea_enable[41] ? 1 : 0;
	WIRE::PE_START_IN_42 = Pea_enable[42] ? 1 : 0;
	WIRE::PE_START_IN_43 = Pea_enable[43] ? 1 : 0;
	WIRE::PE_START_IN_44 = Pea_enable[44] ? 1 : 0;
	WIRE::PE_START_IN_45 = Pea_enable[45] ? 1 : 0;
	WIRE::PE_START_IN_46 = Pea_enable[46] ? 1 : 0;
	WIRE::PE_START_IN_47 = Pea_enable[47] ? 1 : 0;
	WIRE::PE_START_IN_48 = Pea_enable[48] ? 1 : 0;
	WIRE::PE_START_IN_49 = Pea_enable[49] ? 1 : 0;
	WIRE::PE_START_IN_50 = Pea_enable[50] ? 1 : 0;
	WIRE::PE_START_IN_51 = Pea_enable[51] ? 1 : 0;
	WIRE::PE_START_IN_52 = Pea_enable[52] ? 1 : 0;
	WIRE::PE_START_IN_53 = Pea_enable[53] ? 1 : 0;
	WIRE::PE_START_IN_54 = Pea_enable[54] ? 1 : 0;
	WIRE::PE_START_IN_55 = Pea_enable[55] ? 1 : 0;
	WIRE::PE_START_IN_56 = Pea_enable[56] ? 1 : 0;
	WIRE::PE_START_IN_57 = Pea_enable[57] ? 1 : 0;
	WIRE::PE_START_IN_58 = Pea_enable[58] ? 1 : 0;
	WIRE::PE_START_IN_59 = Pea_enable[59] ? 1 : 0;
	WIRE::PE_START_IN_60 = Pea_enable[60] ? 1 : 0;
	WIRE::PE_START_IN_61 = Pea_enable[61] ? 1 : 0;
	WIRE::PE_START_IN_62 = Pea_enable[62] ? 1 : 0;
	WIRE::PE_START_IN_63 = Pea_enable[63] ? 1 : 0;
	WIRE::LOAD_START_IN_F_0 = Lf_enable[0] ? 1 : 0;
	WIRE::LOAD_START_IN_F_1 = Lf_enable[1] ? 1 : 0;
	WIRE::LOAD_START_IN_F_2 = Lf_enable[2] ? 1 : 0;
	WIRE::LOAD_START_IN_F_3 = Lf_enable[3] ? 1 : 0;
	WIRE::LOAD_START_IN_F_4 = Lf_enable[4] ? 1 : 0;
	WIRE::LOAD_START_IN_F_5 = Lf_enable[5] ? 1 : 0;
	WIRE::LOAD_START_IN_F_6 = Lf_enable[6] ? 1 : 0;
	WIRE::LOAD_START_IN_F_7 = Lf_enable[7] ? 1 : 0;

	WIRE::LOAD_START_IN_W_0 = Lw_enable[0] ? 1 : 0;
	WIRE::LOAD_START_IN_W_1 = Lw_enable[1] ? 1 : 0;
	WIRE::LOAD_START_IN_W_2 = Lw_enable[2] ? 1 : 0;
	WIRE::LOAD_START_IN_W_3 = Lw_enable[3] ? 1 : 0;
	WIRE::LOAD_START_IN_W_4 = Lw_enable[4] ? 1 : 0;
	WIRE::LOAD_START_IN_W_5 = Lw_enable[5] ? 1 : 0;
	WIRE::LOAD_START_IN_W_6 = Lw_enable[6] ? 1 : 0;
	WIRE::LOAD_START_IN_W_7 = Lw_enable[7] ? 1 : 0;
	WIRE::LOAD_START_IN_W_8 = Lw_enable[8] ? 1 : 0;
	WIRE::LOAD_START_IN_W_9 = Lw_enable[9] ? 1 : 0;
	WIRE::LOAD_START_IN_W_10 = Lw_enable[10] ? 1 : 0;
	WIRE::LOAD_START_IN_W_11 = Lw_enable[11] ? 1 : 0;
	WIRE::LOAD_START_IN_W_12 = Lw_enable[12] ? 1 : 0;
	WIRE::LOAD_START_IN_W_13 = Lw_enable[13] ? 1 : 0;
	WIRE::LOAD_START_IN_W_14 = Lw_enable[14] ? 1 : 0;
	WIRE::LOAD_START_IN_W_15 = Lw_enable[15] ? 1 : 0;
	WIRE::LOAD_START_IN_W_16 = Lw_enable[16] ? 1 : 0;
	WIRE::LOAD_START_IN_W_17 = Lw_enable[17] ? 1 : 0;
	WIRE::LOAD_START_IN_W_18 = Lw_enable[18] ? 1 : 0;
	WIRE::LOAD_START_IN_W_19 = Lw_enable[19] ? 1 : 0;
	WIRE::LOAD_START_IN_W_20 = Lw_enable[20] ? 1 : 0;
	WIRE::LOAD_START_IN_W_21 = Lw_enable[21] ? 1 : 0;
	WIRE::LOAD_START_IN_W_22 = Lw_enable[22] ? 1 : 0;
	WIRE::LOAD_START_IN_W_23 = Lw_enable[23] ? 1 : 0;
	WIRE::LOAD_START_IN_W_24 = Lw_enable[24] ? 1 : 0;
	WIRE::LOAD_START_IN_W_25 = Lw_enable[25] ? 1 : 0;
	WIRE::LOAD_START_IN_W_26 = Lw_enable[26] ? 1 : 0;
	WIRE::LOAD_START_IN_W_27 = Lw_enable[27] ? 1 : 0;
	WIRE::LOAD_START_IN_W_28 = Lw_enable[28] ? 1 : 0;
	WIRE::LOAD_START_IN_W_29 = Lw_enable[29] ? 1 : 0;
	WIRE::LOAD_START_IN_W_30 = Lw_enable[30] ? 1 : 0;
	WIRE::LOAD_START_IN_W_31 = Lw_enable[31] ? 1 : 0;
	WIRE::LOAD_START_IN_W_32 = Lw_enable[32] ? 1 : 0;
	WIRE::LOAD_START_IN_W_33 = Lw_enable[33] ? 1 : 0;
	WIRE::LOAD_START_IN_W_34 = Lw_enable[34] ? 1 : 0;
	WIRE::LOAD_START_IN_W_35 = Lw_enable[35] ? 1 : 0;
	WIRE::LOAD_START_IN_W_36 = Lw_enable[36] ? 1 : 0;
	WIRE::LOAD_START_IN_W_37 = Lw_enable[37] ? 1 : 0;
	WIRE::LOAD_START_IN_W_38 = Lw_enable[38] ? 1 : 0;
	WIRE::LOAD_START_IN_W_39 = Lw_enable[39] ? 1 : 0;
	WIRE::LOAD_START_IN_W_40 = Lw_enable[40] ? 1 : 0;
	WIRE::LOAD_START_IN_W_41 = Lw_enable[41] ? 1 : 0;
	WIRE::LOAD_START_IN_W_42 = Lw_enable[42] ? 1 : 0;
	WIRE::LOAD_START_IN_W_43 = Lw_enable[43] ? 1 : 0;
	WIRE::LOAD_START_IN_W_44 = Lw_enable[44] ? 1 : 0;
	WIRE::LOAD_START_IN_W_45 = Lw_enable[45] ? 1 : 0;
	WIRE::LOAD_START_IN_W_46 = Lw_enable[46] ? 1 : 0;
	WIRE::LOAD_START_IN_W_47 = Lw_enable[47] ? 1 : 0;
	WIRE::LOAD_START_IN_W_48 = Lw_enable[48] ? 1 : 0;
	WIRE::LOAD_START_IN_W_49 = Lw_enable[49] ? 1 : 0;
	WIRE::LOAD_START_IN_W_50 = Lw_enable[50] ? 1 : 0;
	WIRE::LOAD_START_IN_W_51 = Lw_enable[51] ? 1 : 0;
	WIRE::LOAD_START_IN_W_52 = Lw_enable[52] ? 1 : 0;
	WIRE::LOAD_START_IN_W_53 = Lw_enable[53] ? 1 : 0;
	WIRE::LOAD_START_IN_W_54 = Lw_enable[54] ? 1 : 0;
	WIRE::LOAD_START_IN_W_55 = Lw_enable[55] ? 1 : 0;
	WIRE::LOAD_START_IN_W_56 = Lw_enable[56] ? 1 : 0;
	WIRE::LOAD_START_IN_W_57 = Lw_enable[57] ? 1 : 0;
	WIRE::LOAD_START_IN_W_58 = Lw_enable[58] ? 1 : 0;
	WIRE::LOAD_START_IN_W_59 = Lw_enable[59] ? 1 : 0;
	WIRE::LOAD_START_IN_W_60 = Lw_enable[60] ? 1 : 0;
	WIRE::LOAD_START_IN_W_61 = Lw_enable[61] ? 1 : 0;
	WIRE::LOAD_START_IN_W_62 = Lw_enable[62] ? 1 : 0;
	WIRE::LOAD_START_IN_W_63 = Lw_enable[63] ? 1 : 0;

	WIRE::STORE_START_IN_F_0 = Sf_enable[0] ? 1 : 0;
	WIRE::STORE_START_IN_F_1 = Sf_enable[1] ? 1 : 0;
	WIRE::STORE_START_IN_F_2 = Sf_enable[2] ? 1 : 0;
	WIRE::STORE_START_IN_F_3 = Sf_enable[3] ? 1 : 0;
	WIRE::STORE_START_IN_F_4 = Sf_enable[4] ? 1 : 0;
	WIRE::STORE_START_IN_F_5 = Sf_enable[5] ? 1 : 0;
	WIRE::STORE_START_IN_F_6 = Sf_enable[6] ? 1 : 0;
	WIRE::STORE_START_IN_F_7 = Sf_enable[7] ? 1 : 0;
	return;
}

void PEA::START_SIG_FALLING_EDGE() {
	WIRE::PE_START_IN_0 = 0;
	WIRE::PE_START_IN_1 = 0;
	WIRE::PE_START_IN_2 = 0;
	WIRE::PE_START_IN_3 = 0;
	WIRE::PE_START_IN_4 = 0;
	WIRE::PE_START_IN_5 = 0;
	WIRE::PE_START_IN_6 = 0;
	WIRE::PE_START_IN_7 = 0;
	WIRE::PE_START_IN_8 = 0;
	WIRE::PE_START_IN_9 = 0;
	WIRE::PE_START_IN_10 = 0;
	WIRE::PE_START_IN_11 = 0;
	WIRE::PE_START_IN_12 = 0;
	WIRE::PE_START_IN_13 = 0;
	WIRE::PE_START_IN_14 = 0;
	WIRE::PE_START_IN_15 = 0;
	WIRE::PE_START_IN_16 = 0;
	WIRE::PE_START_IN_17 = 0;
	WIRE::PE_START_IN_18 = 0;
	WIRE::PE_START_IN_19 = 0;
	WIRE::PE_START_IN_20 = 0;
	WIRE::PE_START_IN_21 = 0;
	WIRE::PE_START_IN_22 = 0;
	WIRE::PE_START_IN_23 = 0;
	WIRE::PE_START_IN_24 = 0;
	WIRE::PE_START_IN_25 = 0;
	WIRE::PE_START_IN_26 = 0;
	WIRE::PE_START_IN_27 = 0;
	WIRE::PE_START_IN_28 = 0;
	WIRE::PE_START_IN_29 = 0;
	WIRE::PE_START_IN_30 = 0;
	WIRE::PE_START_IN_31 = 0;
	WIRE::PE_START_IN_32 = 0;
	WIRE::PE_START_IN_33 = 0;
	WIRE::PE_START_IN_34 = 0;
	WIRE::PE_START_IN_35 = 0;
	WIRE::PE_START_IN_36 = 0;
	WIRE::PE_START_IN_37 = 0;
	WIRE::PE_START_IN_38 = 0;
	WIRE::PE_START_IN_39 = 0;
	WIRE::PE_START_IN_40 = 0;
	WIRE::PE_START_IN_41 = 0;
	WIRE::PE_START_IN_42 = 0;
	WIRE::PE_START_IN_43 = 0;
	WIRE::PE_START_IN_44 = 0;
	WIRE::PE_START_IN_45 = 0;
	WIRE::PE_START_IN_46 = 0;
	WIRE::PE_START_IN_47 = 0;
	WIRE::PE_START_IN_48 = 0;
	WIRE::PE_START_IN_49 = 0;
	WIRE::PE_START_IN_50 = 0;
	WIRE::PE_START_IN_51 = 0;
	WIRE::PE_START_IN_52 = 0;
	WIRE::PE_START_IN_53 = 0;
	WIRE::PE_START_IN_54 = 0;
	WIRE::PE_START_IN_55 = 0;
	WIRE::PE_START_IN_56 = 0;
	WIRE::PE_START_IN_57 = 0;
	WIRE::PE_START_IN_58 = 0;
	WIRE::PE_START_IN_59 = 0;
	WIRE::PE_START_IN_60 = 0;
	WIRE::PE_START_IN_61 = 0;
	WIRE::PE_START_IN_62 = 0;
	WIRE::PE_START_IN_63 = 0;
	WIRE::LOAD_START_IN_F_0 = 0;
	WIRE::LOAD_START_IN_F_1 = 0;
	WIRE::LOAD_START_IN_F_2 = 0;
	WIRE::LOAD_START_IN_F_3 = 0;
	WIRE::LOAD_START_IN_F_4 = 0;
	WIRE::LOAD_START_IN_F_5 = 0;
	WIRE::LOAD_START_IN_F_6 = 0;
	WIRE::LOAD_START_IN_F_7 = 0;

	WIRE::LOAD_START_IN_W_0 = 0;
	WIRE::LOAD_START_IN_W_1 = 0;
	WIRE::LOAD_START_IN_W_2 = 0;
	WIRE::LOAD_START_IN_W_3 = 0;
	WIRE::LOAD_START_IN_W_4 = 0;
	WIRE::LOAD_START_IN_W_5 = 0;
	WIRE::LOAD_START_IN_W_6 = 0;
	WIRE::LOAD_START_IN_W_7 = 0;
	WIRE::LOAD_START_IN_W_8 = 0;
	WIRE::LOAD_START_IN_W_9 = 0;
	WIRE::LOAD_START_IN_W_10 = 0;
	WIRE::LOAD_START_IN_W_11 = 0;
	WIRE::LOAD_START_IN_W_12 = 0;
	WIRE::LOAD_START_IN_W_13 = 0;
	WIRE::LOAD_START_IN_W_14 = 0;
	WIRE::LOAD_START_IN_W_15 = 0;
	WIRE::LOAD_START_IN_W_16 = 0;
	WIRE::LOAD_START_IN_W_17 = 0;
	WIRE::LOAD_START_IN_W_18 = 0;
	WIRE::LOAD_START_IN_W_19 = 0;
	WIRE::LOAD_START_IN_W_20 = 0;
	WIRE::LOAD_START_IN_W_21 = 0;
	WIRE::LOAD_START_IN_W_22 = 0;
	WIRE::LOAD_START_IN_W_23 = 0;
	WIRE::LOAD_START_IN_W_24 = 0;
	WIRE::LOAD_START_IN_W_25 = 0;
	WIRE::LOAD_START_IN_W_26 = 0;
	WIRE::LOAD_START_IN_W_27 = 0;
	WIRE::LOAD_START_IN_W_28 = 0;
	WIRE::LOAD_START_IN_W_29 = 0;
	WIRE::LOAD_START_IN_W_30 = 0;
	WIRE::LOAD_START_IN_W_31 = 0;
	WIRE::LOAD_START_IN_W_32 = 0;
	WIRE::LOAD_START_IN_W_33 = 0;
	WIRE::LOAD_START_IN_W_34 = 0;
	WIRE::LOAD_START_IN_W_35 = 0;
	WIRE::LOAD_START_IN_W_36 = 0;
	WIRE::LOAD_START_IN_W_37 = 0;
	WIRE::LOAD_START_IN_W_38 = 0;
	WIRE::LOAD_START_IN_W_39 = 0;
	WIRE::LOAD_START_IN_W_40 = 0;
	WIRE::LOAD_START_IN_W_41 = 0;
	WIRE::LOAD_START_IN_W_42 = 0;
	WIRE::LOAD_START_IN_W_43 = 0;
	WIRE::LOAD_START_IN_W_44 = 0;
	WIRE::LOAD_START_IN_W_45 = 0;
	WIRE::LOAD_START_IN_W_46 = 0;
	WIRE::LOAD_START_IN_W_47 = 0;
	WIRE::LOAD_START_IN_W_48 = 0;
	WIRE::LOAD_START_IN_W_49 = 0;
	WIRE::LOAD_START_IN_W_50 = 0;
	WIRE::LOAD_START_IN_W_51 = 0;
	WIRE::LOAD_START_IN_W_52 = 0;
	WIRE::LOAD_START_IN_W_53 = 0;
	WIRE::LOAD_START_IN_W_54 = 0;
	WIRE::LOAD_START_IN_W_55 = 0;
	WIRE::LOAD_START_IN_W_56 = 0;
	WIRE::LOAD_START_IN_W_57 = 0;
	WIRE::LOAD_START_IN_W_58 = 0;
	WIRE::LOAD_START_IN_W_59 = 0;
	WIRE::LOAD_START_IN_W_60 = 0;
	WIRE::LOAD_START_IN_W_61 = 0;
	WIRE::LOAD_START_IN_W_62 = 0;
	WIRE::LOAD_START_IN_W_63 = 0;

	WIRE::STORE_START_IN_F_0 = 0;
	WIRE::STORE_START_IN_F_1 = 0;
	WIRE::STORE_START_IN_F_2 = 0;
	WIRE::STORE_START_IN_F_3 = 0;
	WIRE::STORE_START_IN_F_4 = 0;
	WIRE::STORE_START_IN_F_5 = 0;
	WIRE::STORE_START_IN_F_6 = 0;
	WIRE::STORE_START_IN_F_7 = 0;
	return;
}

//void PEA::PEA_ENABLE(bool* Pea_enable[], bool* Lf_enable, bool* Lw_enable, bool* Sf_enable) {
void PEA::PEA_ENABLE(bool* Pea_enable, bool* Lf_enable, bool* Lw_enable, bool* Sf_enable) {
	WIRE::PE_ENABLE_IN_0 = Pea_enable[0] ? 1 : 0;
	WIRE::PE_ENABLE_IN_1 = Pea_enable[1] ? 1 : 0;
	WIRE::PE_ENABLE_IN_2 = Pea_enable[2] ? 1 : 0;
	WIRE::PE_ENABLE_IN_3 = Pea_enable[3] ? 1 : 0;
	WIRE::PE_ENABLE_IN_4 = Pea_enable[4] ? 1 : 0;
	WIRE::PE_ENABLE_IN_5 = Pea_enable[5] ? 1 : 0;
	WIRE::PE_ENABLE_IN_6 = Pea_enable[6] ? 1 : 0;
	WIRE::PE_ENABLE_IN_7 = Pea_enable[7] ? 1 : 0;
	WIRE::PE_ENABLE_IN_8 = Pea_enable[8] ? 1 : 0;
	WIRE::PE_ENABLE_IN_9 = Pea_enable[9] ? 1 : 0;
	WIRE::PE_ENABLE_IN_10 = Pea_enable[10] ? 1 : 0;
	WIRE::PE_ENABLE_IN_11 = Pea_enable[11] ? 1 : 0;
	WIRE::PE_ENABLE_IN_12 = Pea_enable[12] ? 1 : 0;
	WIRE::PE_ENABLE_IN_13 = Pea_enable[13] ? 1 : 0;
	WIRE::PE_ENABLE_IN_14 = Pea_enable[14] ? 1 : 0;
	WIRE::PE_ENABLE_IN_15 = Pea_enable[15] ? 1 : 0;
	WIRE::PE_ENABLE_IN_16 = Pea_enable[16] ? 1 : 0;
	WIRE::PE_ENABLE_IN_17 = Pea_enable[17] ? 1 : 0;
	WIRE::PE_ENABLE_IN_18 = Pea_enable[18] ? 1 : 0;
	WIRE::PE_ENABLE_IN_19 = Pea_enable[19] ? 1 : 0;
	WIRE::PE_ENABLE_IN_20 = Pea_enable[20] ? 1 : 0;
	WIRE::PE_ENABLE_IN_21 = Pea_enable[21] ? 1 : 0;
	WIRE::PE_ENABLE_IN_22 = Pea_enable[22] ? 1 : 0;
	WIRE::PE_ENABLE_IN_23 = Pea_enable[23] ? 1 : 0;
	WIRE::PE_ENABLE_IN_24 = Pea_enable[24] ? 1 : 0;
	WIRE::PE_ENABLE_IN_25 = Pea_enable[25] ? 1 : 0;
	WIRE::PE_ENABLE_IN_26 = Pea_enable[26] ? 1 : 0;
	WIRE::PE_ENABLE_IN_27 = Pea_enable[27] ? 1 : 0;
	WIRE::PE_ENABLE_IN_28 = Pea_enable[28] ? 1 : 0;
	WIRE::PE_ENABLE_IN_29 = Pea_enable[29] ? 1 : 0;
	WIRE::PE_ENABLE_IN_30 = Pea_enable[30] ? 1 : 0;
	WIRE::PE_ENABLE_IN_31 = Pea_enable[31] ? 1 : 0;
	WIRE::PE_ENABLE_IN_32 = Pea_enable[32] ? 1 : 0;
	WIRE::PE_ENABLE_IN_33 = Pea_enable[33] ? 1 : 0;
	WIRE::PE_ENABLE_IN_34 = Pea_enable[34] ? 1 : 0;
	WIRE::PE_ENABLE_IN_35 = Pea_enable[35] ? 1 : 0;
	WIRE::PE_ENABLE_IN_36 = Pea_enable[36] ? 1 : 0;
	WIRE::PE_ENABLE_IN_37 = Pea_enable[37] ? 1 : 0;
	WIRE::PE_ENABLE_IN_38 = Pea_enable[38] ? 1 : 0;
	WIRE::PE_ENABLE_IN_39 = Pea_enable[39] ? 1 : 0;
	WIRE::PE_ENABLE_IN_40 = Pea_enable[40] ? 1 : 0;
	WIRE::PE_ENABLE_IN_41 = Pea_enable[41] ? 1 : 0;
	WIRE::PE_ENABLE_IN_42 = Pea_enable[42] ? 1 : 0;
	WIRE::PE_ENABLE_IN_43 = Pea_enable[43] ? 1 : 0;
	WIRE::PE_ENABLE_IN_44 = Pea_enable[44] ? 1 : 0;
	WIRE::PE_ENABLE_IN_45 = Pea_enable[45] ? 1 : 0;
	WIRE::PE_ENABLE_IN_46 = Pea_enable[46] ? 1 : 0;
	WIRE::PE_ENABLE_IN_47 = Pea_enable[47] ? 1 : 0;
	WIRE::PE_ENABLE_IN_48 = Pea_enable[48] ? 1 : 0;
	WIRE::PE_ENABLE_IN_49 = Pea_enable[49] ? 1 : 0;
	WIRE::PE_ENABLE_IN_50 = Pea_enable[50] ? 1 : 0;
	WIRE::PE_ENABLE_IN_51 = Pea_enable[51] ? 1 : 0;
	WIRE::PE_ENABLE_IN_52 = Pea_enable[52] ? 1 : 0;
	WIRE::PE_ENABLE_IN_53 = Pea_enable[53] ? 1 : 0;
	WIRE::PE_ENABLE_IN_54 = Pea_enable[54] ? 1 : 0;
	WIRE::PE_ENABLE_IN_55 = Pea_enable[55] ? 1 : 0;
	WIRE::PE_ENABLE_IN_56 = Pea_enable[56] ? 1 : 0;
	WIRE::PE_ENABLE_IN_57 = Pea_enable[57] ? 1 : 0;
	WIRE::PE_ENABLE_IN_58 = Pea_enable[58] ? 1 : 0;
	WIRE::PE_ENABLE_IN_59 = Pea_enable[59] ? 1 : 0;
	WIRE::PE_ENABLE_IN_60 = Pea_enable[60] ? 1 : 0;
	WIRE::PE_ENABLE_IN_61 = Pea_enable[61] ? 1 : 0;
	WIRE::PE_ENABLE_IN_62 = Pea_enable[62] ? 1 : 0;
	WIRE::PE_ENABLE_IN_63 = Pea_enable[63] ? 1 : 0;
	WIRE::LOAD_ENABLE_IN_F_0 = Lf_enable[0] ? 1 : 0;
	WIRE::LOAD_ENABLE_IN_F_1 = Lf_enable[1] ? 1 : 0;
	WIRE::LOAD_ENABLE_IN_F_2 = Lf_enable[2] ? 1 : 0;
	WIRE::LOAD_ENABLE_IN_F_3 = Lf_enable[3] ? 1 : 0;
	WIRE::LOAD_ENABLE_IN_F_4 = Lf_enable[4] ? 1 : 0;
	WIRE::LOAD_ENABLE_IN_F_5 = Lf_enable[5] ? 1 : 0;
	WIRE::LOAD_ENABLE_IN_F_6 = Lf_enable[6] ? 1 : 0;
	WIRE::LOAD_ENABLE_IN_F_7 = Lf_enable[7] ? 1 : 0;

	WIRE::LOAD_ENABLE_IN_W_0 = Lw_enable[0] ? 1 : 0;
	WIRE::LOAD_ENABLE_IN_W_1 = Lw_enable[1] ? 1 : 0;
	WIRE::LOAD_ENABLE_IN_W_2 = Lw_enable[2] ? 1 : 0;
	WIRE::LOAD_ENABLE_IN_W_3 = Lw_enable[3] ? 1 : 0;
	WIRE::LOAD_ENABLE_IN_W_4 = Lw_enable[4] ? 1 : 0;
	WIRE::LOAD_ENABLE_IN_W_5 = Lw_enable[5] ? 1 : 0;
	WIRE::LOAD_ENABLE_IN_W_6 = Lw_enable[6] ? 1 : 0;
	WIRE::LOAD_ENABLE_IN_W_7 = Lw_enable[7] ? 1 : 0;
	WIRE::LOAD_ENABLE_IN_W_8 = Lw_enable[8] ? 1 : 0;
	WIRE::LOAD_ENABLE_IN_W_9 = Lw_enable[9] ? 1 : 0;
	WIRE::LOAD_ENABLE_IN_W_10 = Lw_enable[10] ? 1 : 0;
	WIRE::LOAD_ENABLE_IN_W_11 = Lw_enable[11] ? 1 : 0;
	WIRE::LOAD_ENABLE_IN_W_12 = Lw_enable[12] ? 1 : 0;
	WIRE::LOAD_ENABLE_IN_W_13 = Lw_enable[13] ? 1 : 0;
	WIRE::LOAD_ENABLE_IN_W_14 = Lw_enable[14] ? 1 : 0;
	WIRE::LOAD_ENABLE_IN_W_15 = Lw_enable[15] ? 1 : 0;
	WIRE::LOAD_ENABLE_IN_W_16 = Lw_enable[16] ? 1 : 0;
	WIRE::LOAD_ENABLE_IN_W_17 = Lw_enable[17] ? 1 : 0;
	WIRE::LOAD_ENABLE_IN_W_18 = Lw_enable[18] ? 1 : 0;
	WIRE::LOAD_ENABLE_IN_W_19 = Lw_enable[19] ? 1 : 0;
	WIRE::LOAD_ENABLE_IN_W_20 = Lw_enable[20] ? 1 : 0;
	WIRE::LOAD_ENABLE_IN_W_21 = Lw_enable[21] ? 1 : 0;
	WIRE::LOAD_ENABLE_IN_W_22 = Lw_enable[22] ? 1 : 0;
	WIRE::LOAD_ENABLE_IN_W_23 = Lw_enable[23] ? 1 : 0;
	WIRE::LOAD_ENABLE_IN_W_24 = Lw_enable[24] ? 1 : 0;
	WIRE::LOAD_ENABLE_IN_W_25 = Lw_enable[25] ? 1 : 0;
	WIRE::LOAD_ENABLE_IN_W_26 = Lw_enable[26] ? 1 : 0;
	WIRE::LOAD_ENABLE_IN_W_27 = Lw_enable[27] ? 1 : 0;
	WIRE::LOAD_ENABLE_IN_W_28 = Lw_enable[28] ? 1 : 0;
	WIRE::LOAD_ENABLE_IN_W_29 = Lw_enable[29] ? 1 : 0;
	WIRE::LOAD_ENABLE_IN_W_30 = Lw_enable[30] ? 1 : 0;
	WIRE::LOAD_ENABLE_IN_W_31 = Lw_enable[31] ? 1 : 0;
	WIRE::LOAD_ENABLE_IN_W_32 = Lw_enable[32] ? 1 : 0;
	WIRE::LOAD_ENABLE_IN_W_33 = Lw_enable[33] ? 1 : 0;
	WIRE::LOAD_ENABLE_IN_W_34 = Lw_enable[34] ? 1 : 0;
	WIRE::LOAD_ENABLE_IN_W_35 = Lw_enable[35] ? 1 : 0;
	WIRE::LOAD_ENABLE_IN_W_36 = Lw_enable[36] ? 1 : 0;
	WIRE::LOAD_ENABLE_IN_W_37 = Lw_enable[37] ? 1 : 0;
	WIRE::LOAD_ENABLE_IN_W_38 = Lw_enable[38] ? 1 : 0;
	WIRE::LOAD_ENABLE_IN_W_39 = Lw_enable[39] ? 1 : 0;
	WIRE::LOAD_ENABLE_IN_W_40 = Lw_enable[40] ? 1 : 0;
	WIRE::LOAD_ENABLE_IN_W_41 = Lw_enable[41] ? 1 : 0;
	WIRE::LOAD_ENABLE_IN_W_42 = Lw_enable[42] ? 1 : 0;
	WIRE::LOAD_ENABLE_IN_W_43 = Lw_enable[43] ? 1 : 0;
	WIRE::LOAD_ENABLE_IN_W_44 = Lw_enable[44] ? 1 : 0;
	WIRE::LOAD_ENABLE_IN_W_45 = Lw_enable[45] ? 1 : 0;
	WIRE::LOAD_ENABLE_IN_W_46 = Lw_enable[46] ? 1 : 0;
	WIRE::LOAD_ENABLE_IN_W_47 = Lw_enable[47] ? 1 : 0;
	WIRE::LOAD_ENABLE_IN_W_48 = Lw_enable[48] ? 1 : 0;
	WIRE::LOAD_ENABLE_IN_W_49 = Lw_enable[49] ? 1 : 0;
	WIRE::LOAD_ENABLE_IN_W_50 = Lw_enable[50] ? 1 : 0;
	WIRE::LOAD_ENABLE_IN_W_51 = Lw_enable[51] ? 1 : 0;
	WIRE::LOAD_ENABLE_IN_W_52 = Lw_enable[52] ? 1 : 0;
	WIRE::LOAD_ENABLE_IN_W_53 = Lw_enable[53] ? 1 : 0;
	WIRE::LOAD_ENABLE_IN_W_54 = Lw_enable[54] ? 1 : 0;
	WIRE::LOAD_ENABLE_IN_W_55 = Lw_enable[55] ? 1 : 0;
	WIRE::LOAD_ENABLE_IN_W_56 = Lw_enable[56] ? 1 : 0;
	WIRE::LOAD_ENABLE_IN_W_57 = Lw_enable[57] ? 1 : 0;
	WIRE::LOAD_ENABLE_IN_W_58 = Lw_enable[58] ? 1 : 0;
	WIRE::LOAD_ENABLE_IN_W_59 = Lw_enable[59] ? 1 : 0;
	WIRE::LOAD_ENABLE_IN_W_60 = Lw_enable[60] ? 1 : 0;
	WIRE::LOAD_ENABLE_IN_W_61 = Lw_enable[61] ? 1 : 0;
	WIRE::LOAD_ENABLE_IN_W_62 = Lw_enable[62] ? 1 : 0;
	//WIRE::LOAD_ENABLE_IN_W_63 = Lf_enable[63] ? 1 : 0;//?????
	WIRE::LOAD_ENABLE_IN_W_63 = Lw_enable[63] ? 1 : 0;

	WIRE::STORE_ENABLE_IN_F_0 = Sf_enable[0] ? 1 : 0;
	WIRE::STORE_ENABLE_IN_F_1 = Sf_enable[1] ? 1 : 0;
	WIRE::STORE_ENABLE_IN_F_2 = Sf_enable[2] ? 1 : 0;
	WIRE::STORE_ENABLE_IN_F_3 = Sf_enable[3] ? 1 : 0;
	WIRE::STORE_ENABLE_IN_F_4 = Sf_enable[4] ? 1 : 0;
	WIRE::STORE_ENABLE_IN_F_5 = Sf_enable[5] ? 1 : 0;
	WIRE::STORE_ENABLE_IN_F_6 = Sf_enable[6] ? 1 : 0;
	WIRE::STORE_ENABLE_IN_F_7 = Sf_enable[7] ? 1 : 0;
	return;
}

bool PEA::PEA_CHECKIDLE() {
	return (
		WIRE::PE_IDLE_OUT_0 == 1 &&
		WIRE::PE_IDLE_OUT_1 == 1 &&
		WIRE::PE_IDLE_OUT_2 == 1 &&
		WIRE::PE_IDLE_OUT_3 == 1 &&
		WIRE::PE_IDLE_OUT_4 == 1 &&
		WIRE::PE_IDLE_OUT_5 == 1 &&
		WIRE::PE_IDLE_OUT_6 == 1 &&
		WIRE::PE_IDLE_OUT_7 == 1 &&
		WIRE::PE_IDLE_OUT_8 == 1 &&
		WIRE::PE_IDLE_OUT_9 == 1 &&
		WIRE::PE_IDLE_OUT_10 == 1 &&
		WIRE::PE_IDLE_OUT_11 == 1 &&
		WIRE::PE_IDLE_OUT_12 == 1 &&
		WIRE::PE_IDLE_OUT_13 == 1 &&
		WIRE::PE_IDLE_OUT_14 == 1 &&
		WIRE::PE_IDLE_OUT_15 == 1 &&
		WIRE::PE_IDLE_OUT_16 == 1 &&
		WIRE::PE_IDLE_OUT_17 == 1 &&
		WIRE::PE_IDLE_OUT_18 == 1 &&
		WIRE::PE_IDLE_OUT_19 == 1 &&
		WIRE::PE_IDLE_OUT_20 == 1 &&
		WIRE::PE_IDLE_OUT_21 == 1 &&
		WIRE::PE_IDLE_OUT_22 == 1 &&
		WIRE::PE_IDLE_OUT_23 == 1 &&
		WIRE::PE_IDLE_OUT_24 == 1 &&
		WIRE::PE_IDLE_OUT_25 == 1 &&
		WIRE::PE_IDLE_OUT_26 == 1 &&
		WIRE::PE_IDLE_OUT_27 == 1 &&
		WIRE::PE_IDLE_OUT_28 == 1 &&
		WIRE::PE_IDLE_OUT_29 == 1 &&
		WIRE::PE_IDLE_OUT_30 == 1 &&
		WIRE::PE_IDLE_OUT_31 == 1 &&
		WIRE::PE_IDLE_OUT_32 == 1 &&
		WIRE::PE_IDLE_OUT_33 == 1 &&
		WIRE::PE_IDLE_OUT_34 == 1 &&
		WIRE::PE_IDLE_OUT_35 == 1 &&
		WIRE::PE_IDLE_OUT_36 == 1 &&
		WIRE::PE_IDLE_OUT_37 == 1 &&
		WIRE::PE_IDLE_OUT_38 == 1 &&
		WIRE::PE_IDLE_OUT_39 == 1 &&
		WIRE::PE_IDLE_OUT_40 == 1 &&
		WIRE::PE_IDLE_OUT_41 == 1 &&
		WIRE::PE_IDLE_OUT_42 == 1 &&
		WIRE::PE_IDLE_OUT_43 == 1 &&
		WIRE::PE_IDLE_OUT_44 == 1 &&
		WIRE::PE_IDLE_OUT_45 == 1 &&
		WIRE::PE_IDLE_OUT_46 == 1 &&
		WIRE::PE_IDLE_OUT_47 == 1 &&
		WIRE::PE_IDLE_OUT_48 == 1 &&
		WIRE::PE_IDLE_OUT_49 == 1 &&
		WIRE::PE_IDLE_OUT_50 == 1 &&
		WIRE::PE_IDLE_OUT_51 == 1 &&
		WIRE::PE_IDLE_OUT_52 == 1 &&
		WIRE::PE_IDLE_OUT_53 == 1 &&
		WIRE::PE_IDLE_OUT_54 == 1 &&
		WIRE::PE_IDLE_OUT_55 == 1 &&
		WIRE::PE_IDLE_OUT_56 == 1 &&
		WIRE::PE_IDLE_OUT_57 == 1 &&
		WIRE::PE_IDLE_OUT_58 == 1 &&
		WIRE::PE_IDLE_OUT_59 == 1 &&
		WIRE::PE_IDLE_OUT_60 == 1 &&
		WIRE::PE_IDLE_OUT_61 == 1 &&
		WIRE::PE_IDLE_OUT_62 == 1 &&
		WIRE::PE_IDLE_OUT_63 == 1 &&
		WIRE::LOAD_IDLE_OUT_F_0 == 1 &&
		WIRE::LOAD_IDLE_OUT_F_1 == 1 &&
		WIRE::LOAD_IDLE_OUT_F_2 == 1 &&
		WIRE::LOAD_IDLE_OUT_F_3 == 1 &&
		WIRE::LOAD_IDLE_OUT_F_4 == 1 &&
		WIRE::LOAD_IDLE_OUT_F_5 == 1 &&
		WIRE::LOAD_IDLE_OUT_F_6 == 1 &&
		WIRE::LOAD_IDLE_OUT_F_7 == 1 &&
		WIRE::LOAD_IDLE_OUT_W_0 == 1 &&
		WIRE::LOAD_IDLE_OUT_W_1 == 1 &&
		WIRE::LOAD_IDLE_OUT_W_2 == 1 &&
		WIRE::LOAD_IDLE_OUT_W_3 == 1 &&
		WIRE::LOAD_IDLE_OUT_W_4 == 1 &&
		WIRE::LOAD_IDLE_OUT_W_5 == 1 &&
		WIRE::LOAD_IDLE_OUT_W_6 == 1 &&
		WIRE::LOAD_IDLE_OUT_W_7 == 1 &&
		WIRE::LOAD_IDLE_OUT_W_8 == 1 &&
		WIRE::LOAD_IDLE_OUT_W_9 == 1 &&
		WIRE::LOAD_IDLE_OUT_W_10 == 1 &&
		WIRE::LOAD_IDLE_OUT_W_11 == 1 &&
		WIRE::LOAD_IDLE_OUT_W_12 == 1 &&
		WIRE::LOAD_IDLE_OUT_W_13 == 1 &&
		WIRE::LOAD_IDLE_OUT_W_14 == 1 &&
		WIRE::LOAD_IDLE_OUT_W_15 == 1 &&
		WIRE::LOAD_IDLE_OUT_W_16 == 1 &&
		WIRE::LOAD_IDLE_OUT_W_17 == 1 &&
		WIRE::LOAD_IDLE_OUT_W_18 == 1 &&
		WIRE::LOAD_IDLE_OUT_W_19 == 1 &&
		WIRE::LOAD_IDLE_OUT_W_20 == 1 &&
		WIRE::LOAD_IDLE_OUT_W_21 == 1 &&
		WIRE::LOAD_IDLE_OUT_W_22 == 1 &&
		WIRE::LOAD_IDLE_OUT_W_23 == 1 &&
		WIRE::LOAD_IDLE_OUT_W_24 == 1 &&
		WIRE::LOAD_IDLE_OUT_W_25 == 1 &&
		WIRE::LOAD_IDLE_OUT_W_26 == 1 &&
		WIRE::LOAD_IDLE_OUT_W_27 == 1 &&
		WIRE::LOAD_IDLE_OUT_W_28 == 1 &&
		WIRE::LOAD_IDLE_OUT_W_29 == 1 &&
		WIRE::LOAD_IDLE_OUT_W_30 == 1 &&
		WIRE::LOAD_IDLE_OUT_W_31 == 1 &&
		WIRE::LOAD_IDLE_OUT_W_32 == 1 &&
		WIRE::LOAD_IDLE_OUT_W_33 == 1 &&
		WIRE::LOAD_IDLE_OUT_W_34 == 1 &&
		WIRE::LOAD_IDLE_OUT_W_35 == 1 &&
		WIRE::LOAD_IDLE_OUT_W_36 == 1 &&
		WIRE::LOAD_IDLE_OUT_W_37 == 1 &&
		WIRE::LOAD_IDLE_OUT_W_38 == 1 &&
		WIRE::LOAD_IDLE_OUT_W_39 == 1 &&
		WIRE::LOAD_IDLE_OUT_W_40 == 1 &&
		WIRE::LOAD_IDLE_OUT_W_41 == 1 &&
		WIRE::LOAD_IDLE_OUT_W_42 == 1 &&
		WIRE::LOAD_IDLE_OUT_W_43 == 1 &&
		WIRE::LOAD_IDLE_OUT_W_44 == 1 &&
		WIRE::LOAD_IDLE_OUT_W_45 == 1 &&
		WIRE::LOAD_IDLE_OUT_W_46 == 1 &&
		WIRE::LOAD_IDLE_OUT_W_47 == 1 &&
		WIRE::LOAD_IDLE_OUT_W_48 == 1 &&
		WIRE::LOAD_IDLE_OUT_W_49 == 1 &&
		WIRE::LOAD_IDLE_OUT_W_50 == 1 &&
		WIRE::LOAD_IDLE_OUT_W_51 == 1 &&
		WIRE::LOAD_IDLE_OUT_W_52 == 1 &&
		WIRE::LOAD_IDLE_OUT_W_53 == 1 &&
		WIRE::LOAD_IDLE_OUT_W_54 == 1 &&
		WIRE::LOAD_IDLE_OUT_W_55 == 1 &&
		WIRE::LOAD_IDLE_OUT_W_56 == 1 &&
		WIRE::LOAD_IDLE_OUT_W_57 == 1 &&
		WIRE::LOAD_IDLE_OUT_W_58 == 1 &&
		WIRE::LOAD_IDLE_OUT_W_59 == 1 &&
		WIRE::LOAD_IDLE_OUT_W_60 == 1 &&
		WIRE::LOAD_IDLE_OUT_W_61 == 1 &&
		WIRE::LOAD_IDLE_OUT_W_62 == 1 &&
		WIRE::LOAD_IDLE_OUT_W_63 == 1 &&
		WIRE::STORE_IDLE_OUT_F_0 == 1 &&
		WIRE::STORE_IDLE_OUT_F_1 == 1 &&
		WIRE::STORE_IDLE_OUT_F_2 == 1 &&
		WIRE::STORE_IDLE_OUT_F_3 == 1 &&
		WIRE::STORE_IDLE_OUT_F_4 == 1 &&
		WIRE::STORE_IDLE_OUT_F_5 == 1 &&
		WIRE::STORE_IDLE_OUT_F_6 == 1 &&
		WIRE::STORE_IDLE_OUT_F_7 == 1);
}

void PEA::PEA_OUTPUT() {
	GR::GR_OUTPUT();
	if (WIRE::PE_ENABLE_IN_0 == 1) {
		PEA::PEid[0].PE_OUTPUT();
	}
	if (WIRE::PE_ENABLE_IN_1 == 1) {
		PEA::PEid[1].PE_OUTPUT();
	}
	if (WIRE::PE_ENABLE_IN_2 == 1) {
		PEA::PEid[2].PE_OUTPUT();
	}
	if (WIRE::PE_ENABLE_IN_3 == 1) {
		PEA::PEid[3].PE_OUTPUT();
	}
	if (WIRE::PE_ENABLE_IN_4 == 1) {
		PEA::PEid[4].PE_OUTPUT();
	}
	if (WIRE::PE_ENABLE_IN_5 == 1) {
		PEA::PEid[5].PE_OUTPUT();
	}
	if (WIRE::PE_ENABLE_IN_6 == 1) {
		PEA::PEid[6].PE_OUTPUT();
	}
	if (WIRE::PE_ENABLE_IN_7 == 1) {
		PEA::PEid[7].PE_OUTPUT();
	}
	if (WIRE::PE_ENABLE_IN_8 == 1) {
		PEA::PEid[8].PE_OUTPUT();
	}
	if (WIRE::PE_ENABLE_IN_9 == 1) {
		PEA::PEid[9].PE_OUTPUT();
	}
	if (WIRE::PE_ENABLE_IN_10 == 1) {
		PEA::PEid[10].PE_OUTPUT();
	}
	if (WIRE::PE_ENABLE_IN_11 == 1) {
		PEA::PEid[11].PE_OUTPUT();
	}
	if (WIRE::PE_ENABLE_IN_12 == 1) {
		PEA::PEid[12].PE_OUTPUT();
	}
	if (WIRE::PE_ENABLE_IN_13 == 1) {
		PEA::PEid[13].PE_OUTPUT();
	}
	if (WIRE::PE_ENABLE_IN_14 == 1) {
		PEA::PEid[14].PE_OUTPUT();
	}
	if (WIRE::PE_ENABLE_IN_15 == 1) {
		PEA::PEid[15].PE_OUTPUT();
	}
	if (WIRE::PE_ENABLE_IN_16 == 1) {
		PEA::PEid[16].PE_OUTPUT();
	}
	if (WIRE::PE_ENABLE_IN_17 == 1) {
		PEA::PEid[17].PE_OUTPUT();
	}
	if (WIRE::PE_ENABLE_IN_18 == 1) {
		PEA::PEid[18].PE_OUTPUT();
	}
	if (WIRE::PE_ENABLE_IN_19 == 1) {
		PEA::PEid[19].PE_OUTPUT();
	}
	if (WIRE::PE_ENABLE_IN_20 == 1) {
		PEA::PEid[20].PE_OUTPUT();
	}
	if (WIRE::PE_ENABLE_IN_21 == 1) {
		PEA::PEid[21].PE_OUTPUT();
	}
	if (WIRE::PE_ENABLE_IN_22 == 1) {
		PEA::PEid[22].PE_OUTPUT();
	}
	if (WIRE::PE_ENABLE_IN_23 == 1) {
		PEA::PEid[23].PE_OUTPUT();
	}
	if (WIRE::PE_ENABLE_IN_24 == 1) {
		PEA::PEid[24].PE_OUTPUT();
	}
	if (WIRE::PE_ENABLE_IN_25 == 1) {
		PEA::PEid[25].PE_OUTPUT();
	}
	if (WIRE::PE_ENABLE_IN_26 == 1) {
		PEA::PEid[26].PE_OUTPUT();
	}
	if (WIRE::PE_ENABLE_IN_27 == 1) {
		PEA::PEid[27].PE_OUTPUT();
	}
	if (WIRE::PE_ENABLE_IN_28 == 1) {
		PEA::PEid[28].PE_OUTPUT();
	}
	if (WIRE::PE_ENABLE_IN_29 == 1) {
		PEA::PEid[29].PE_OUTPUT();
	}
	if (WIRE::PE_ENABLE_IN_30 == 1) {
		PEA::PEid[30].PE_OUTPUT();
	}
	if (WIRE::PE_ENABLE_IN_31 == 1) {
		PEA::PEid[31].PE_OUTPUT();
	}
	if (WIRE::PE_ENABLE_IN_32 == 1) {
		PEA::PEid[32].PE_OUTPUT();
	}
	if (WIRE::PE_ENABLE_IN_33 == 1) {
		PEA::PEid[33].PE_OUTPUT();
	}
	if (WIRE::PE_ENABLE_IN_34 == 1) {
		PEA::PEid[34].PE_OUTPUT();
	}
	if (WIRE::PE_ENABLE_IN_35 == 1) {
		PEA::PEid[35].PE_OUTPUT();
	}
	if (WIRE::PE_ENABLE_IN_36 == 1) {
		PEA::PEid[36].PE_OUTPUT();
	}
	if (WIRE::PE_ENABLE_IN_37 == 1) {
		PEA::PEid[37].PE_OUTPUT();
	}
	if (WIRE::PE_ENABLE_IN_38 == 1) {
		PEA::PEid[38].PE_OUTPUT();
	}
	if (WIRE::PE_ENABLE_IN_39 == 1) {
		PEA::PEid[39].PE_OUTPUT();
	}
	if (WIRE::PE_ENABLE_IN_40 == 1) {
		PEA::PEid[40].PE_OUTPUT();
	}
	if (WIRE::PE_ENABLE_IN_41 == 1) {
		PEA::PEid[41].PE_OUTPUT();
	}
	if (WIRE::PE_ENABLE_IN_42 == 1) {
		PEA::PEid[42].PE_OUTPUT();
	}
	if (WIRE::PE_ENABLE_IN_43 == 1) {
		PEA::PEid[43].PE_OUTPUT();
	}
	if (WIRE::PE_ENABLE_IN_44 == 1) {
		PEA::PEid[44].PE_OUTPUT();
	}
	if (WIRE::PE_ENABLE_IN_45 == 1) {
		PEA::PEid[45].PE_OUTPUT();
	}
	if (WIRE::PE_ENABLE_IN_46 == 1) {
		PEA::PEid[46].PE_OUTPUT();
	}
	if (WIRE::PE_ENABLE_IN_47 == 1) {
		PEA::PEid[47].PE_OUTPUT();
	}
	if (WIRE::PE_ENABLE_IN_48 == 1) {
		PEA::PEid[48].PE_OUTPUT();
	}
	if (WIRE::PE_ENABLE_IN_49 == 1) {
		PEA::PEid[49].PE_OUTPUT();
	}
	if (WIRE::PE_ENABLE_IN_50 == 1) {
		PEA::PEid[50].PE_OUTPUT();
	}
	if (WIRE::PE_ENABLE_IN_51 == 1) {
		PEA::PEid[51].PE_OUTPUT();
	}
	if (WIRE::PE_ENABLE_IN_52 == 1) {
		PEA::PEid[52].PE_OUTPUT();
	}
	if (WIRE::PE_ENABLE_IN_53 == 1) {
		PEA::PEid[53].PE_OUTPUT();
	}
	if (WIRE::PE_ENABLE_IN_54 == 1) {
		PEA::PEid[54].PE_OUTPUT();
	}
	if (WIRE::PE_ENABLE_IN_55 == 1) {
		PEA::PEid[55].PE_OUTPUT();
	}
	if (WIRE::PE_ENABLE_IN_56 == 1) {
		PEA::PEid[56].PE_OUTPUT();
	}
	if (WIRE::PE_ENABLE_IN_57 == 1) {
		PEA::PEid[57].PE_OUTPUT();
	}
	if (WIRE::PE_ENABLE_IN_58 == 1) {
		PEA::PEid[58].PE_OUTPUT();
	}
	if (WIRE::PE_ENABLE_IN_59 == 1) {
		PEA::PEid[59].PE_OUTPUT();
	}
	if (WIRE::PE_ENABLE_IN_60 == 1) {
		PEA::PEid[60].PE_OUTPUT();
	}
	if (WIRE::PE_ENABLE_IN_61 == 1) {
		PEA::PEid[61].PE_OUTPUT();
	}
	if (WIRE::PE_ENABLE_IN_62 == 1) {
		PEA::PEid[62].PE_OUTPUT();
	}
	if (WIRE::PE_ENABLE_IN_63 == 1) {
		PEA::PEid[63].PE_OUTPUT();
	}
	/*if (WIRE::LOAD_ENABLE_IN_F_0 == 1) {
		LOAD_F0.LSU_OUTPUT();
	}
	if (WIRE::LOAD_ENABLE_IN_F_1 == 1) {
		LOAD_F1.LSU_OUTPUT();
	}
	if (WIRE::LOAD_ENABLE_IN_F_2 == 1) {
		LOAD_F2.LSU_OUTPUT();
	}
	if (WIRE::LOAD_ENABLE_IN_F_3 == 1) {
		LOAD_F3.LSU_OUTPUT();
	}
	if (WIRE::LOAD_ENABLE_IN_F_4 == 1) {
		LOAD_F4.LSU_OUTPUT();
	}
	if (WIRE::LOAD_ENABLE_IN_F_5 == 1) {
		LOAD_F5.LSU_OUTPUT();
	}
	if (WIRE::LOAD_ENABLE_IN_F_6 == 1) {
		LOAD_F6.LSU_OUTPUT();
	}
	if (WIRE::LOAD_ENABLE_IN_F_7 == 1) {
		LOAD_F7.LSU_OUTPUT();
	}
	if (WIRE::LOAD_ENABLE_IN_W_0 == 1) {
		LOAD_W0.LSU_OUTPUT();
	}
	if (WIRE::LOAD_ENABLE_IN_W_1 == 1) {
		LOAD_W1.LSU_OUTPUT();
	}
	if (WIRE::LOAD_ENABLE_IN_W_2 == 1) {
		LOAD_W2.LSU_OUTPUT();
	}
	if (WIRE::LOAD_ENABLE_IN_W_3 == 1) {
		LOAD_W3.LSU_OUTPUT();
	}
	if (WIRE::LOAD_ENABLE_IN_W_4 == 1) {
		LOAD_W4.LSU_OUTPUT();
	}
	if (WIRE::LOAD_ENABLE_IN_W_5 == 1) {
		LOAD_W5.LSU_OUTPUT();
	}
	if (WIRE::LOAD_ENABLE_IN_W_6 == 1) {
		LOAD_W6.LSU_OUTPUT();
	}
	if (WIRE::LOAD_ENABLE_IN_W_7 == 1) {
		LOAD_W7.LSU_OUTPUT();
	}
	if (WIRE::LOAD_ENABLE_IN_W_8 == 1) {
		LOAD_W8.LSU_OUTPUT();
	}
	if (WIRE::LOAD_ENABLE_IN_W_9 == 1) {
		LOAD_W9.LSU_OUTPUT();
	}
	if (WIRE::LOAD_ENABLE_IN_W_10 == 1) {
		LOAD_W10.LSU_OUTPUT();
	}
	if (WIRE::LOAD_ENABLE_IN_W_11 == 1) {
		LOAD_W11.LSU_OUTPUT();
	}
	if (WIRE::LOAD_ENABLE_IN_W_12 == 1) {
		LOAD_W12.LSU_OUTPUT();
	}
	if (WIRE::LOAD_ENABLE_IN_W_13 == 1) {
		LOAD_W13.LSU_OUTPUT();
	}
	if (WIRE::LOAD_ENABLE_IN_W_14 == 1) {
		LOAD_W14.LSU_OUTPUT();
	}
	if (WIRE::LOAD_ENABLE_IN_W_15 == 1) {
		LOAD_W15.LSU_OUTPUT();
	}
	if (WIRE::LOAD_ENABLE_IN_W_16 == 1) {
		LOAD_W16.LSU_OUTPUT();
	}
	if (WIRE::LOAD_ENABLE_IN_W_17 == 1) {
		LOAD_W17.LSU_OUTPUT();
	}
	if (WIRE::LOAD_ENABLE_IN_W_18 == 1) {
		LOAD_W18.LSU_OUTPUT();
	}
	if (WIRE::LOAD_ENABLE_IN_W_19 == 1) {
		LOAD_W19.LSU_OUTPUT();
	}
	if (WIRE::LOAD_ENABLE_IN_W_20 == 1) {
		LOAD_W20.LSU_OUTPUT();
	}
	if (WIRE::LOAD_ENABLE_IN_W_21 == 1) {
		LOAD_W21.LSU_OUTPUT();
	}
	if (WIRE::LOAD_ENABLE_IN_W_22 == 1) {
		LOAD_W22.LSU_OUTPUT();
	}
	if (WIRE::LOAD_ENABLE_IN_W_23 == 1) {
		LOAD_W23.LSU_OUTPUT();
	}
	if (WIRE::LOAD_ENABLE_IN_W_24 == 1) {
		LOAD_W24.LSU_OUTPUT();
	}
	if (WIRE::LOAD_ENABLE_IN_W_25 == 1) {
		LOAD_W25.LSU_OUTPUT();
	}
	if (WIRE::LOAD_ENABLE_IN_W_26 == 1) {
		LOAD_W26.LSU_OUTPUT();
	}
	if (WIRE::LOAD_ENABLE_IN_W_27 == 1) {
		LOAD_W27.LSU_OUTPUT();
	}
	if (WIRE::LOAD_ENABLE_IN_W_28 == 1) {
		LOAD_W28.LSU_OUTPUT();
	}
	if (WIRE::LOAD_ENABLE_IN_W_29 == 1) {
		LOAD_W29.LSU_OUTPUT();
	}
	if (WIRE::LOAD_ENABLE_IN_W_30 == 1) {
		LOAD_W30.LSU_OUTPUT();
	}
	if (WIRE::LOAD_ENABLE_IN_W_31 == 1) {
		LOAD_W31.LSU_OUTPUT();
	}
	if (WIRE::LOAD_ENABLE_IN_W_32 == 1) {
		LOAD_W32.LSU_OUTPUT();
	}
	if (WIRE::LOAD_ENABLE_IN_W_33 == 1) {
		LOAD_W33.LSU_OUTPUT();
	}
	if (WIRE::LOAD_ENABLE_IN_W_34 == 1) {
		LOAD_W34.LSU_OUTPUT();
	}
	if (WIRE::LOAD_ENABLE_IN_W_35 == 1) {
		LOAD_W35.LSU_OUTPUT();
	}
	if (WIRE::LOAD_ENABLE_IN_W_36 == 1) {
		LOAD_W36.LSU_OUTPUT();
	}
	if (WIRE::LOAD_ENABLE_IN_W_37 == 1) {
		LOAD_W37.LSU_OUTPUT();
	}
	if (WIRE::LOAD_ENABLE_IN_W_38 == 1) {
		LOAD_W38.LSU_OUTPUT();
	}
	if (WIRE::LOAD_ENABLE_IN_W_39 == 1) {
		LOAD_W39.LSU_OUTPUT();
	}
	if (WIRE::LOAD_ENABLE_IN_W_40 == 1) {
		LOAD_W40.LSU_OUTPUT();
	}
	if (WIRE::LOAD_ENABLE_IN_W_41 == 1) {
		LOAD_W41.LSU_OUTPUT();
	}
	if (WIRE::LOAD_ENABLE_IN_W_42 == 1) {
		LOAD_W42.LSU_OUTPUT();
	}
	if (WIRE::LOAD_ENABLE_IN_W_43 == 1) {
		LOAD_W43.LSU_OUTPUT();
	}
	if (WIRE::LOAD_ENABLE_IN_W_44 == 1) {
		LOAD_W44.LSU_OUTPUT();
	}
	if (WIRE::LOAD_ENABLE_IN_W_45 == 1) {
		LOAD_W45.LSU_OUTPUT();
	}
	if (WIRE::LOAD_ENABLE_IN_W_46 == 1) {
		LOAD_W46.LSU_OUTPUT();
	}
	if (WIRE::LOAD_ENABLE_IN_W_47 == 1) {
		LOAD_W47.LSU_OUTPUT();
	}
	if (WIRE::LOAD_ENABLE_IN_W_48 == 1) {
		LOAD_W48.LSU_OUTPUT();
	}
	if (WIRE::LOAD_ENABLE_IN_W_49 == 1) {
		LOAD_W49.LSU_OUTPUT();
	}
	if (WIRE::LOAD_ENABLE_IN_W_50 == 1) {
		LOAD_W50.LSU_OUTPUT();
	}
	if (WIRE::LOAD_ENABLE_IN_W_51 == 1) {
		LOAD_W51.LSU_OUTPUT();
	}
	if (WIRE::LOAD_ENABLE_IN_W_52 == 1) {
		LOAD_W52.LSU_OUTPUT();
	}
	if (WIRE::LOAD_ENABLE_IN_W_53 == 1) {
		LOAD_W53.LSU_OUTPUT();
	}
	if (WIRE::LOAD_ENABLE_IN_W_54 == 1) {
		LOAD_W54.LSU_OUTPUT();
	}
	if (WIRE::LOAD_ENABLE_IN_W_55 == 1) {
		LOAD_W55.LSU_OUTPUT();
	}
	if (WIRE::LOAD_ENABLE_IN_W_56 == 1) {
		LOAD_W56.LSU_OUTPUT();
	}
	if (WIRE::LOAD_ENABLE_IN_W_57 == 1) {
		LOAD_W57.LSU_OUTPUT();
	}
	if (WIRE::LOAD_ENABLE_IN_W_58 == 1) {
		LOAD_W58.LSU_OUTPUT();
	}
	if (WIRE::LOAD_ENABLE_IN_W_59 == 1) {
		LOAD_W59.LSU_OUTPUT();
	}
	if (WIRE::LOAD_ENABLE_IN_W_60 == 1) {
		LOAD_W60.LSU_OUTPUT();
	}
	if (WIRE::LOAD_ENABLE_IN_W_61 == 1) {
		LOAD_W61.LSU_OUTPUT();
	}
	if (WIRE::LOAD_ENABLE_IN_W_62 == 1) {
		LOAD_W62.LSU_OUTPUT();
	}
	if (WIRE::LOAD_ENABLE_IN_W_63 == 1) {
		LOAD_W63.LSU_OUTPUT();
	}
	if (WIRE::STORE_ENABLE_IN_F_0 == 1) {
		STORE_F0.LSU_OUTPUT();
	}
	if (WIRE::STORE_ENABLE_IN_F_1 == 1) {
		STORE_F1.LSU_OUTPUT();
	}
	if (WIRE::STORE_ENABLE_IN_F_2 == 1) {
		STORE_F2.LSU_OUTPUT();
	}
	if (WIRE::STORE_ENABLE_IN_F_3 == 1) {
		STORE_F3.LSU_OUTPUT();
	}
	if (WIRE::STORE_ENABLE_IN_F_4 == 1) {
		STORE_F4.LSU_OUTPUT();
	}
	if (WIRE::STORE_ENABLE_IN_F_5 == 1) {
		STORE_F5.LSU_OUTPUT();
	}
	if (WIRE::STORE_ENABLE_IN_F_6 == 1) {
		STORE_F6.LSU_OUTPUT();
	}
	if (WIRE::STORE_ENABLE_IN_F_7 == 1) {
		STORE_F7.LSU_OUTPUT();
	}*/
	return;
}

 void PEA::PEA_EXEC(DebugParam_t  &debug, bool &debugflag, int &taskid, std::ostringstream &os) {
	 GR::GR_EXEC();
	if (WIRE::PE_ENABLE_IN_0 == 1) {
		PEA::PEid[0].PE_EXEC( debug, debugflag, taskid,  os);
	}
	if (WIRE::PE_ENABLE_IN_1 == 1) {
		PEA::PEid[1].PE_EXEC( debug, debugflag, taskid,  os);
	}
	if (WIRE::PE_ENABLE_IN_2 == 1) {
		PEA::PEid[2].PE_EXEC( debug, debugflag, taskid,  os);
	}
	if (WIRE::PE_ENABLE_IN_3 == 1) {
		PEA::PEid[3].PE_EXEC( debug, debugflag, taskid,  os);
	}
	if (WIRE::PE_ENABLE_IN_4 == 1) {
		PEA::PEid[4].PE_EXEC( debug, debugflag, taskid,  os);
	}
	if (WIRE::PE_ENABLE_IN_5 == 1) {
		PEA::PEid[5].PE_EXEC( debug, debugflag, taskid,  os);
	}
	if (WIRE::PE_ENABLE_IN_6 == 1) {
		PEA::PEid[6].PE_EXEC( debug, debugflag, taskid,  os);
	}
	if (WIRE::PE_ENABLE_IN_7 == 1) {
		PEA::PEid[7].PE_EXEC( debug, debugflag, taskid,  os);
	}
	if (WIRE::PE_ENABLE_IN_8 == 1) {
		PEA::PEid[8].PE_EXEC( debug, debugflag, taskid,  os);
	}
	if (WIRE::PE_ENABLE_IN_9 == 1) {
		PEA::PEid[9].PE_EXEC( debug, debugflag, taskid,  os);
	}
	if (WIRE::PE_ENABLE_IN_10 == 1) {
		PEA::PEid[10].PE_EXEC( debug, debugflag, taskid,  os);
	}
	if (WIRE::PE_ENABLE_IN_11 == 1) {
		PEA::PEid[11].PE_EXEC( debug, debugflag, taskid,  os);
	}
	if (WIRE::PE_ENABLE_IN_12 == 1) {
		PEA::PEid[12].PE_EXEC( debug, debugflag, taskid,  os);
	}
	if (WIRE::PE_ENABLE_IN_13 == 1) {
		PEA::PEid[13].PE_EXEC( debug, debugflag, taskid,  os);
	}
	if (WIRE::PE_ENABLE_IN_14 == 1) {
		PEA::PEid[14].PE_EXEC( debug, debugflag, taskid,  os);
	}
	if (WIRE::PE_ENABLE_IN_15 == 1) {
		PEA::PEid[15].PE_EXEC( debug, debugflag, taskid,  os);
	}
	if (WIRE::PE_ENABLE_IN_16 == 1) {
		PEA::PEid[16].PE_EXEC( debug, debugflag, taskid,  os);
	}
	if (WIRE::PE_ENABLE_IN_17 == 1) {
		PEA::PEid[17].PE_EXEC( debug, debugflag, taskid,  os);
	}
	if (WIRE::PE_ENABLE_IN_18 == 1) {
		PEA::PEid[18].PE_EXEC( debug, debugflag, taskid,  os);
	}
	if (WIRE::PE_ENABLE_IN_19 == 1) {
		PEA::PEid[19].PE_EXEC( debug, debugflag, taskid,  os);
	}
	if (WIRE::PE_ENABLE_IN_20 == 1) {
		PEA::PEid[20].PE_EXEC( debug, debugflag, taskid,  os);
	}
	if (WIRE::PE_ENABLE_IN_21 == 1) {
		PEA::PEid[21].PE_EXEC( debug, debugflag, taskid,  os);
	}
	if (WIRE::PE_ENABLE_IN_22 == 1) {
		PEA::PEid[22].PE_EXEC( debug, debugflag, taskid,  os);
	}
	if (WIRE::PE_ENABLE_IN_23 == 1) {
		PEA::PEid[23].PE_EXEC( debug, debugflag, taskid,  os);
	}
	if (WIRE::PE_ENABLE_IN_24 == 1) {
		PEA::PEid[24].PE_EXEC( debug, debugflag, taskid,  os);
	}
	if (WIRE::PE_ENABLE_IN_25 == 1) {
		PEA::PEid[25].PE_EXEC( debug, debugflag, taskid,  os);
	}
	if (WIRE::PE_ENABLE_IN_26 == 1) {
		PEA::PEid[26].PE_EXEC( debug, debugflag, taskid,  os);
	}
	if (WIRE::PE_ENABLE_IN_27 == 1) {
		PEA::PEid[27].PE_EXEC( debug, debugflag, taskid,  os);
	}
	if (WIRE::PE_ENABLE_IN_28 == 1) {
		PEA::PEid[28].PE_EXEC( debug, debugflag, taskid,  os);
	}
	if (WIRE::PE_ENABLE_IN_29 == 1) {
		PEA::PEid[29].PE_EXEC( debug, debugflag, taskid,  os);
	}
	if (WIRE::PE_ENABLE_IN_30 == 1) {
		PEA::PEid[30].PE_EXEC( debug, debugflag, taskid,  os);
	}
	if (WIRE::PE_ENABLE_IN_31 == 1) {
		PEA::PEid[31].PE_EXEC( debug, debugflag, taskid,  os);
	}
	if (WIRE::PE_ENABLE_IN_32 == 1) {
		PEA::PEid[32].PE_EXEC( debug, debugflag, taskid,  os);
	}
	if (WIRE::PE_ENABLE_IN_33 == 1) {
		PEA::PEid[33].PE_EXEC( debug, debugflag, taskid,  os);
	}
	if (WIRE::PE_ENABLE_IN_34 == 1) {
		PEA::PEid[34].PE_EXEC( debug, debugflag, taskid,  os);
	}
	if (WIRE::PE_ENABLE_IN_35 == 1) {
		PEA::PEid[35].PE_EXEC( debug, debugflag, taskid,  os);
	}
	if (WIRE::PE_ENABLE_IN_36 == 1) {
		PEA::PEid[36].PE_EXEC( debug, debugflag, taskid,  os);
	}
	if (WIRE::PE_ENABLE_IN_37 == 1) {
		PEA::PEid[37].PE_EXEC( debug, debugflag, taskid,  os);
	}
	if (WIRE::PE_ENABLE_IN_38 == 1) {
		PEA::PEid[38].PE_EXEC( debug, debugflag, taskid,  os);
	}
	if (WIRE::PE_ENABLE_IN_39 == 1) {
		PEA::PEid[39].PE_EXEC( debug, debugflag, taskid,  os);
	}
	if (WIRE::PE_ENABLE_IN_40 == 1) {
		PEA::PEid[40].PE_EXEC( debug, debugflag, taskid,  os);
	}
	if (WIRE::PE_ENABLE_IN_41 == 1) {
		PEA::PEid[41].PE_EXEC( debug, debugflag, taskid,  os);
	}
	if (WIRE::PE_ENABLE_IN_42 == 1) {
		PEA::PEid[42].PE_EXEC( debug, debugflag, taskid,  os);
	}
	if (WIRE::PE_ENABLE_IN_43 == 1) {
		PEA::PEid[43].PE_EXEC( debug, debugflag, taskid,  os);
	}
	if (WIRE::PE_ENABLE_IN_44 == 1) {
		PEA::PEid[44].PE_EXEC( debug, debugflag, taskid,  os);
	}
	if (WIRE::PE_ENABLE_IN_45 == 1) {
		PEA::PEid[45].PE_EXEC( debug, debugflag, taskid,  os);
	}
	if (WIRE::PE_ENABLE_IN_46 == 1) {
		PEA::PEid[46].PE_EXEC( debug, debugflag, taskid,  os);
	}
	if (WIRE::PE_ENABLE_IN_47 == 1) {
		PEA::PEid[47].PE_EXEC( debug, debugflag, taskid,  os);
	}
	if (WIRE::PE_ENABLE_IN_48 == 1) {
		PEA::PEid[48].PE_EXEC( debug, debugflag, taskid,  os);
	}
	if (WIRE::PE_ENABLE_IN_49 == 1) {
		PEA::PEid[49].PE_EXEC( debug, debugflag, taskid,  os);
	}
	if (WIRE::PE_ENABLE_IN_50 == 1) {
		PEA::PEid[50].PE_EXEC( debug, debugflag, taskid,  os);
	}
	if (WIRE::PE_ENABLE_IN_51 == 1) {
		PEA::PEid[51].PE_EXEC( debug, debugflag, taskid,  os);
	}
	if (WIRE::PE_ENABLE_IN_52 == 1) {
		PEA::PEid[52].PE_EXEC( debug, debugflag, taskid,  os);
	}
	if (WIRE::PE_ENABLE_IN_53 == 1) {
		PEA::PEid[53].PE_EXEC( debug, debugflag, taskid,  os);
	}
	if (WIRE::PE_ENABLE_IN_54 == 1) {
		PEA::PEid[54].PE_EXEC( debug, debugflag, taskid,  os);
	}
	if (WIRE::PE_ENABLE_IN_55 == 1) {
		PEA::PEid[55].PE_EXEC( debug, debugflag, taskid,  os);
	}
	if (WIRE::PE_ENABLE_IN_56 == 1) {
		PEA::PEid[56].PE_EXEC( debug, debugflag, taskid,  os);
	}
	if (WIRE::PE_ENABLE_IN_57 == 1) {
		PEA::PEid[57].PE_EXEC( debug, debugflag, taskid,  os);
	}
	if (WIRE::PE_ENABLE_IN_58 == 1) {
		PEA::PEid[58].PE_EXEC( debug, debugflag, taskid,  os);
	}
	if (WIRE::PE_ENABLE_IN_59 == 1) {
		PEA::PEid[59].PE_EXEC( debug, debugflag, taskid,  os);
	}
	if (WIRE::PE_ENABLE_IN_60 == 1) {
		PEA::PEid[60].PE_EXEC( debug, debugflag, taskid,  os);
	}
	if (WIRE::PE_ENABLE_IN_61 == 1) {
		PEA::PEid[61].PE_EXEC( debug, debugflag, taskid,  os);
	}
	if (WIRE::PE_ENABLE_IN_62 == 1) {
		PEA::PEid[62].PE_EXEC( debug, debugflag, taskid,  os);
	}
	if (WIRE::PE_ENABLE_IN_63 == 1) {
		PEA::PEid[63].PE_EXEC( debug, debugflag, taskid,  os);
	}
	/*if (WIRE::LOAD_ENABLE_IN_F_0 == 1) {
		LOAD_F0.LSU_EXEC();
	}
	if (WIRE::LOAD_ENABLE_IN_F_1 == 1) {
		LOAD_F1.LSU_EXEC();
	}
	if (WIRE::LOAD_ENABLE_IN_F_2 == 1) {
		LOAD_F2.LSU_EXEC();
	}
	if (WIRE::LOAD_ENABLE_IN_F_3 == 1) {
		LOAD_F3.LSU_EXEC();
	}
	if (WIRE::LOAD_ENABLE_IN_F_4 == 1) {
		LOAD_F4.LSU_EXEC();
	}
	if (WIRE::LOAD_ENABLE_IN_F_5 == 1) {
		LOAD_F5.LSU_EXEC();
	}
	if (WIRE::LOAD_ENABLE_IN_F_6 == 1) {
		LOAD_F6.LSU_EXEC();
	}
	if (WIRE::LOAD_ENABLE_IN_F_7 == 1) {
		LOAD_F7.LSU_EXEC();
	}
	if (WIRE::LOAD_ENABLE_IN_W_0 == 1) {
		LOAD_W0.LSU_EXEC();
	}
	if (WIRE::LOAD_ENABLE_IN_W_1 == 1) {
		LOAD_W1.LSU_EXEC();
	}
	if (WIRE::LOAD_ENABLE_IN_W_2 == 1) {
		LOAD_W2.LSU_EXEC();
	}
	if (WIRE::LOAD_ENABLE_IN_W_3 == 1) {
		LOAD_W3.LSU_EXEC();
	}
	if (WIRE::LOAD_ENABLE_IN_W_4 == 1) {
		LOAD_W4.LSU_EXEC();
	}
	if (WIRE::LOAD_ENABLE_IN_W_5 == 1) {
		LOAD_W5.LSU_EXEC();
	}
	if (WIRE::LOAD_ENABLE_IN_W_6 == 1) {
		LOAD_W6.LSU_EXEC();
	}
	if (WIRE::LOAD_ENABLE_IN_W_7 == 1) {
		LOAD_W7.LSU_EXEC();
	}
	if (WIRE::LOAD_ENABLE_IN_W_8 == 1) {
		LOAD_W8.LSU_EXEC();
	}
	if (WIRE::LOAD_ENABLE_IN_W_9 == 1) {
		LOAD_W9.LSU_EXEC();
	}
	if (WIRE::LOAD_ENABLE_IN_W_10 == 1) {
		LOAD_W10.LSU_EXEC();
	}
	if (WIRE::LOAD_ENABLE_IN_W_11 == 1) {
		LOAD_W11.LSU_EXEC();
	}
	if (WIRE::LOAD_ENABLE_IN_W_12 == 1) {
		LOAD_W12.LSU_EXEC();
	}
	if (WIRE::LOAD_ENABLE_IN_W_13 == 1) {
		LOAD_W13.LSU_EXEC();
	}
	if (WIRE::LOAD_ENABLE_IN_W_14 == 1) {
		LOAD_W14.LSU_EXEC();
	}
	if (WIRE::LOAD_ENABLE_IN_W_15 == 1) {
		LOAD_W15.LSU_EXEC();
	}
	if (WIRE::LOAD_ENABLE_IN_W_16 == 1) {
		LOAD_W16.LSU_EXEC();
	}
	if (WIRE::LOAD_ENABLE_IN_W_17 == 1) {
		LOAD_W17.LSU_EXEC();
	}
	if (WIRE::LOAD_ENABLE_IN_W_18 == 1) {
		LOAD_W18.LSU_EXEC();
	}
	if (WIRE::LOAD_ENABLE_IN_W_19 == 1) {
		LOAD_W19.LSU_EXEC();
	}
	if (WIRE::LOAD_ENABLE_IN_W_20 == 1) {
		LOAD_W20.LSU_EXEC();
	}
	if (WIRE::LOAD_ENABLE_IN_W_21 == 1) {
		LOAD_W21.LSU_EXEC();
	}
	if (WIRE::LOAD_ENABLE_IN_W_22 == 1) {
		LOAD_W22.LSU_EXEC();
	}
	if (WIRE::LOAD_ENABLE_IN_W_23 == 1) {
		LOAD_W23.LSU_EXEC();
	}
	if (WIRE::LOAD_ENABLE_IN_W_24 == 1) {
		LOAD_W24.LSU_EXEC();
	}
	if (WIRE::LOAD_ENABLE_IN_W_25 == 1) {
		LOAD_W25.LSU_EXEC();
	}
	if (WIRE::LOAD_ENABLE_IN_W_26 == 1) {
		LOAD_W26.LSU_EXEC();
	}
	if (WIRE::LOAD_ENABLE_IN_W_27 == 1) {
		LOAD_W27.LSU_EXEC();
	}
	if (WIRE::LOAD_ENABLE_IN_W_28 == 1) {
		LOAD_W28.LSU_EXEC();
	}
	if (WIRE::LOAD_ENABLE_IN_W_29 == 1) {
		LOAD_W29.LSU_EXEC();
	}
	if (WIRE::LOAD_ENABLE_IN_W_30 == 1) {
		LOAD_W30.LSU_EXEC();
	}
	if (WIRE::LOAD_ENABLE_IN_W_31 == 1) {
		LOAD_W31.LSU_EXEC();
	}
	if (WIRE::LOAD_ENABLE_IN_W_32 == 1) {
		LOAD_W32.LSU_EXEC();
	}
	if (WIRE::LOAD_ENABLE_IN_W_33 == 1) {
		LOAD_W33.LSU_EXEC();
	}
	if (WIRE::LOAD_ENABLE_IN_W_34 == 1) {
		LOAD_W34.LSU_EXEC();
	}
	if (WIRE::LOAD_ENABLE_IN_W_35 == 1) {
		LOAD_W35.LSU_EXEC();
	}
	if (WIRE::LOAD_ENABLE_IN_W_36 == 1) {
		LOAD_W36.LSU_EXEC();
	}
	if (WIRE::LOAD_ENABLE_IN_W_37 == 1) {
		LOAD_W37.LSU_EXEC();
	}
	if (WIRE::LOAD_ENABLE_IN_W_38 == 1) {
		LOAD_W38.LSU_EXEC();
	}
	if (WIRE::LOAD_ENABLE_IN_W_39 == 1) {
		LOAD_W39.LSU_EXEC();
	}
	if (WIRE::LOAD_ENABLE_IN_W_40 == 1) {
		LOAD_W40.LSU_EXEC();
	}
	if (WIRE::LOAD_ENABLE_IN_W_41 == 1) {
		LOAD_W41.LSU_EXEC();
	}
	if (WIRE::LOAD_ENABLE_IN_W_42 == 1) {
		LOAD_W42.LSU_EXEC();
	}
	if (WIRE::LOAD_ENABLE_IN_W_43 == 1) {
		LOAD_W43.LSU_EXEC();
	}
	if (WIRE::LOAD_ENABLE_IN_W_44 == 1) {
		LOAD_W44.LSU_EXEC();
	}
	if (WIRE::LOAD_ENABLE_IN_W_45 == 1) {
		LOAD_W45.LSU_EXEC();
	}
	if (WIRE::LOAD_ENABLE_IN_W_46 == 1) {
		LOAD_W46.LSU_EXEC();
	}
	if (WIRE::LOAD_ENABLE_IN_W_47 == 1) {
		LOAD_W47.LSU_EXEC();
	}
	if (WIRE::LOAD_ENABLE_IN_W_48 == 1) {
		LOAD_W48.LSU_EXEC();
	}
	if (WIRE::LOAD_ENABLE_IN_W_49 == 1) {
		LOAD_W49.LSU_EXEC();
	}
	if (WIRE::LOAD_ENABLE_IN_W_50 == 1) {
		LOAD_W50.LSU_EXEC();
	}
	if (WIRE::LOAD_ENABLE_IN_W_51 == 1) {
		LOAD_W51.LSU_EXEC();
	}
	if (WIRE::LOAD_ENABLE_IN_W_52 == 1) {
		LOAD_W52.LSU_EXEC();
	}
	if (WIRE::LOAD_ENABLE_IN_W_53 == 1) {
		LOAD_W53.LSU_EXEC();
	}
	if (WIRE::LOAD_ENABLE_IN_W_54 == 1) {
		LOAD_W54.LSU_EXEC();
	}
	if (WIRE::LOAD_ENABLE_IN_W_55 == 1) {
		LOAD_W55.LSU_EXEC();
	}
	if (WIRE::LOAD_ENABLE_IN_W_56 == 1) {
		LOAD_W56.LSU_EXEC();
	}
	if (WIRE::LOAD_ENABLE_IN_W_57 == 1) {
		LOAD_W57.LSU_EXEC();
	}
	if (WIRE::LOAD_ENABLE_IN_W_58 == 1) {
		LOAD_W58.LSU_EXEC();
	}
	if (WIRE::LOAD_ENABLE_IN_W_59 == 1) {
		LOAD_W59.LSU_EXEC();
	}
	if (WIRE::LOAD_ENABLE_IN_W_60 == 1) {
		LOAD_W60.LSU_EXEC();
	}
	if (WIRE::LOAD_ENABLE_IN_W_61 == 1) {
		LOAD_W61.LSU_EXEC();
	}
	if (WIRE::LOAD_ENABLE_IN_W_62 == 1) {
		LOAD_W62.LSU_EXEC();
	}
	if (WIRE::LOAD_ENABLE_IN_W_63 == 1) {
		LOAD_W63.LSU_EXEC();
	}
	if (WIRE::STORE_ENABLE_IN_F_0 == 1) {
		STORE_F0.LSU_EXEC();
	}
	if (WIRE::STORE_ENABLE_IN_F_1 == 1) {
		STORE_F1.LSU_EXEC();
	}
	if (WIRE::STORE_ENABLE_IN_F_2 == 1) {
		STORE_F2.LSU_EXEC();
	}
	if (WIRE::STORE_ENABLE_IN_F_3 == 1) {
		STORE_F3.LSU_EXEC();
	}
	if (WIRE::STORE_ENABLE_IN_F_4 == 1) {
		STORE_F4.LSU_EXEC();
	}
	if (WIRE::STORE_ENABLE_IN_F_5 == 1) {
		STORE_F5.LSU_EXEC();
	}
	if (WIRE::STORE_ENABLE_IN_F_6 == 1) {
		STORE_F6.LSU_EXEC();
	}
	if (WIRE::STORE_ENABLE_IN_F_7 == 1) {
		STORE_F7.LSU_EXEC();
	}*/
	//GR::GR_SHIFT();
	return;
}