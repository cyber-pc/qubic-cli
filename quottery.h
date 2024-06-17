#pragma once
//SC structs
struct QuotteryjoinBet_input {
    uint32_t betId;
    int numberOfSlot;
    uint32_t option;
    uint32_t _placeHolder;
};
struct QuotteryissueBet_input {
    uint8_t betDesc[32];
    uint8_t optionDesc[32*8];
    uint8_t oracleProviderId[32*8];
    uint32_t oracleFees[8];
    uint8_t closeDate[4];
    uint8_t endDate[4];
    uint64_t amountPerSlot;
    uint32_t maxBetSlotPerOption;
    uint32_t numberOfOption;
};
struct qtryBasicInfo_output
{
    uint64_t feePerSlotPerDay; // Amount of qus
    uint64_t gameOperatorFee; // 4 digit number ABCD means AB.CD% | 1234 is 12.34%
    uint64_t shareholderFee; // 4 digit number ABCD means AB.CD% | 1234 is 12.34%
    uint64_t minBetSlotAmount; // amount of qus
    uint64_t burnFee; // percentage
    uint64_t nIssuedBet; // number of issued bet
    uint64_t moneyFlow;
    uint64_t moneyFlowThroughIssueBet;
    uint64_t moneyFlowThroughJoinBet;
    uint64_t moneyFlowThroughFinalizeBet;
    uint64_t earnedAmountForShareHolder;
    uint64_t paidAmountForShareHolder;
    uint64_t earnedAmountForBetWinner;
    uint64_t distributedAmount;
    uint64_t burnedAmount;
    uint8_t gameOperator[32];
};


struct getBetInfo_input {
    uint32_t betId;
};

struct getBetInfo_output {
    // meta data info
    uint32_t betId;
    uint32_t nOption;      // options number
    uint8_t creator[32];
    uint8_t betDesc[32];      // 32 bytes
    uint8_t optionDesc[8*32];  // 8x(32)=256bytes
    uint8_t oracleProviderId[8*32]; // 256x8=2048bytes
    uint32_t oracleFees[8];   // 4x8 = 32 bytes

    uint8_t openDate[4];     // creation date, start to receive bet
    uint8_t closeDate[4];    // stop receiving bet date
    uint8_t endDate[4];       // result date
    // Amounts and numbers
    uint64_t minBetAmount;
    uint32_t maxBetSlotPerOption;
    uint32_t currentBetState[8]; // how many bet slots have been filled on each option
    char betResultWonOption[8];
    char betResultOPId[8];
};

struct getBetOptionDetail_input {
    uint32_t betId;
    uint32_t betOption;
};
struct getBetOptionDetail_output {
    uint8_t bettor[32*1024];
};
struct getActiveBet_output{
    uint32_t count;
    uint32_t betId[1024];
};

struct getActiveBetByCreator_input{
    uint8_t creator[32];
};

struct getActiveBetByCreator_output{
    uint32_t count;
    uint32_t betId[1024];
};

struct publishResult_input{
    uint32_t betId;
    uint32_t winOption;
};
#pragma pack(1)
struct cancelBet_input{
    uint32_t betId;
};
#pragma pop()

void quotteryPrintBetInfo(const char* nodeIp, const int nodePort, int betId);
void quotteryPrintBasicInfo(const char* nodeIp, const int nodePort);
void quotteryPrintBetOptionDetail(const char* nodeIp, const int nodePort, uint32_t betId, uint32_t betOption);
void quotteryPrintActiveBet(const char* nodeIp, const int nodePort);
void quotteryPrintActiveBetByCreator(const char* nodeIp, const int nodePort, const char* identity);
void quotteryCancelBet(const char* nodeIp, const int nodePort, const char* seed, const uint32_t betId, const uint32_t scheduledTickOffset);
void quotteryPublishResult(const char* nodeIp, const int nodePort, const char* seed, const uint32_t betId, const uint32_t winOption, const uint32_t scheduledTickOffset);

// Core function
void quotteryGetActiveBet(const char* nodeIp, const int nodePort, getActiveBet_output& result);

// Get detail information of a bet ID
void quotteryGetBetInfo(
    const char* nodeIp,
    const int nodePort,
    int betId,
    getBetInfo_output& result);

// Join a bet
void quotteryJoinBet(
    const char* nodeIp,
    int nodePort,
    const char* seed,
    uint32_t betId,
    int numberOfBetSlot,
    uint64_t amountPerSlot,
    uint8_t option,
    uint32_t scheduledTickOffset,
    char* txOuputHash = nullptr,
    unsigned int* txTick = nullptr);

// Issue a bet
void quotteryIssueBet(
    const char* nodeIp,
    int nodePort,
    const char* seed,
    uint32_t scheduledTickOffset,
    QuotteryissueBet_input* betInput = nullptr,
    char* txOuputHash = nullptr,
    unsigned int* txTick = nullptr);
