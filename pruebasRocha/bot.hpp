#ifndef BOT_TREE
#define BOT_TREE

class BotTree:Matrix6x7 {
    public:
    bool exploreBot(int R, int C, int player, bool checkPattern = false);

    bool scanTable(int R, int C, int dR, int dC, int player, int &count, bool checkPattern = false);

    int botMove();

    int randomColumn();
}


#endif