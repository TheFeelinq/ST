#pragma once
#include "IFMainFrame.h"
#include "IFSpinButtonCtrl.h"


class CIFTest : public CIFMainFrame
{
GFX_DECLARE_DYNCREATE(CIFTest)
GFX_DECLARE_MESSAGE_MAP(CIFTest)

    struct Rank {
        Rank(int p, const std::n_wstring &n) : points(p), name(n) {}
        Rank(int p, const wchar_t *n) : points(p), name(n) {}

        // Make sortable
        bool operator<(const Rank &lhs) const {
            return this->points < lhs.points;
        }

        int points;
        std::n_wstring name;
    };

public:
    CIFTest(void);
    ~CIFTest(void);

    bool OnCreate(long ln) override;
    void OnUpdate() override;

private:

    void GenerateRanks(int count);

    /// \brief Show the given page
    /// \param page Page Number (0 to N)
    void ShowPage(int page);

    void On_BtnClick();

    void On_SpinButtonClick();

    int On4001(int a1, int a2);
    int On4002(int a1, int a2);
    int On4003(int a1, int a2);
    int OnVisibleStateChange(int a1, int a2);
    int On4005(int a1, int a2);
    int On4006(int a1, int a2);

    void CIFTest::AddRank(const Rank &rank);
    void ClearRanks();

private:
    const static int m_sizeOfPage = 5;
    CIFButton *m_mybutton;
    CIFStatic* m_time_label;
    CIFStatic* m_custom_label;

    CIFStatic* m_list_label[m_sizeOfPage];

    std::n_list<Rank> m_ranks;

    CIFSpinButtonCtrl* m_spin;

};
