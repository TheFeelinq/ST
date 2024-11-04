#pragma once

struct SPartyData
{
private:
    char pad_0000[16]; //0x0000
public:
    int NumberOfMembers; //0x0010
    char pad_0078[0x74];
    int PartyNumber; //0x0088
private:
    BEGIN_FIXTURE()
    ENSURE_OFFSET(NumberOfMembers, 0x0010)
    ENSURE_OFFSET(PartyNumber, 0x0088)
    END_FIXTURE()

    RUN_FIXTURE(SPartyData)
};
