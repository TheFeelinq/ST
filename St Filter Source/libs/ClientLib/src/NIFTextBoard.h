#include "GFX3DFunction/GFontTexture.h"
#include <BSLib/BSLib.h>

class CNIFTextBoard {

public:
    CNIFTextBoard(void);
    virtual ~CNIFTextBoard(void);

    virtual void TB_Func_1(float a2);
    virtual void TB_Func_2();
    virtual void TB_Func_3();
    virtual void TB_Func_4();
    virtual void TB_Func_5(int a2);
    virtual void TB_Func_6(int a2);
    virtual void TB_Func_7();
    virtual char TB_Func_8();
    virtual void TB_Func_9(char a2);
    virtual void TB_Func_10();
    virtual void TB_Func_11();
    virtual void TB_Func_12(const char * str, int a3, int a4);
    virtual void TB_Func_13(std::n_string str, int a3, int a4);

    virtual void TB_Func_14(std::string str, int a3, int a4);
    virtual void TB_Func_15(int a2);
    virtual void TB_Func_16();

private:

    char N000096C1; //0x0004
    char pad_0005[3]; //0x0005
    int N000096C2; //0x0008
    char pad_0xc[0xad-(0x8+4)];
    char N00009BB9; //0x00AD
    char pad_0xae[0xDC-(0xAD+1)];
    int N00009757; //0x00DC
    std::n_string bg_filename_maybe; //0x00E0
    int N00009768; //0x00FC
    char N00009769; //0x0100
    char pad_00101[0x104-(0x0100+1)]; //0x0101
BEGIN_FIXTURE()
        ENSURE_SIZE(0x104)
        ENSURE_OFFSET(N000096C1, 0x004)
        ENSURE_OFFSET(N000096C2, 0x008)
        ENSURE_OFFSET(N00009BB9, 0x0AD)
        ENSURE_OFFSET(N00009757, 0x0DC)
        ENSURE_OFFSET(bg_filename_maybe, 0x0E0)
        ENSURE_OFFSET(N00009768, 0x0FC)
        ENSURE_OFFSET(N00009769, 0x100)
    END_FIXTURE()
    RUN_FIXTURE(CNIFTextBoard)
};
