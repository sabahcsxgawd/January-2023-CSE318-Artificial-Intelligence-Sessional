void Play_AI_vs_AI() {
    random_device device;
    mt19937 generator(device());
    uniform_int_distribution<int> distribution(60, 100);


    int p0maxDepth, p1maxDepth;
    int p0heuristicID, p1heuristicID;
    int weights[2][4];
    bool startingPlayer;

    for(int i = 0; i < 4; i++) {
        weights[0][i] = distribution(generator);
        weights[1][i] = distribution(generator);
    }

    const int maxHeuristicID = (sizeof(heuristicsArr) / sizeof(heuristicsArr[0]));

    cout << "Enter Starting Player ID (Must be 0 or 1) : ";
    cin >> startingPlayer;
    cout << '\n';

    cout << "Enter Player 0's Max Depth : ";
    cin >> p0maxDepth;
    cout << '\n';

    cout << "Enter Player 1's Max Depth : ";
    cin >> p1maxDepth;
    cout << '\n';

    cout << "Enter Player 0's Choice of Heuristic (Must be between 1 - " << maxHeuristicID << ") : ";
    cin >> p0heuristicID;
    p0heuristicID--;
    cout << '\n';

    cout << "Enter Player 1's Choice of Heuristic (Must be between 1 - " << maxHeuristicID << ") : ";
    cin >> p1heuristicID;
    p1heuristicID--;
    cout << '\n';

    Player p0(0, p0maxDepth, p0heuristicID);
    Player p1(1, p1maxDepth, p1heuristicID);


    GameState *initialState = GameState::getInitialState(startingPlayer);;
    pair<int, int> pp;

 
    initialState->printState();

    while(true) {
        if(!initialState->isFinalState()) {
            if(!initialState->getWhichPlayer()) {
                W1 = weights[0][0]; W2 = weights[0][1]; W3 = weights[0][2]; W4 = weights[0][3];
                pp = p0.minimaxAlphaBetaPruning(initialState, 0, INT_MIN, INT_MAX, true);
                cout << "\nPlayer 0 picks bin no : " << pp.second << "\n\n";
            }
            else {
                W1 = weights[1][0]; W2 = weights[1][1]; W3 = weights[1][2]; W4 = weights[1][3];
                pp = p1.minimaxAlphaBetaPruning(initialState, 1, INT_MIN, INT_MAX, true);
                cout << "\nPlayer 1 picks bin no : " << pp.second << "\n\n";
            }
            initialState = initialState->changeState(pp.second);
            initialState->printState();
        }
        else {
            initialState->finalStoneCollection();
            cout << "\n\n=========FINAL STATE=========\n\n";
            initialState->printState();
            cout <<"\n\n";
            if(initialState->getWinner() == 1) {
                cout << "Player 1 has won\n\n";
            }
            else if(initialState->getWinner() == 2) {
                cout << "Draw\n\n";
            }
            else {             
                cout << "Player 0 has won\n\n";
            }
            break;
        }   
    }

    delete initialState;
}

void Play_HUMAN_vs_AI() {
    random_device device;
    mt19937 generator(device());
    uniform_int_distribution<int> distribution(60, 100);


    int p1maxDepth;
    int p1heuristicID;
    int weights[1][4];
    bool startingPlayer;

    for(int i = 0; i < 4; i++) {
        weights[0][i] = distribution(generator);
    }

    const int maxHeuristicID = (sizeof(heuristicsArr) / sizeof(heuristicsArr[0]));

    cout << "\nPlayer ID of Human is 0 and Player ID of AI is 1\n";
    cout << "Enter Starting Player ID (Must be 0 or 1) : ";
    cin >> startingPlayer;
    cout << '\n';

    cout << "Enter Player 1's Max Depth : ";
    cin >> p1maxDepth;
    cout << '\n';

    cout << "Enter Player 1's Choice of Heuristic (Must be between 1 - " << maxHeuristicID << ") : ";
    cin >> p1heuristicID;
    p1heuristicID--;
    cout << '\n';

    Player p0(0, 0, 0);
    Player p1(1, p1maxDepth, p1heuristicID);


    GameState *initialState = GameState::getInitialState(startingPlayer);;
    pair<int, int> pp;

 
    initialState->printState();

    while(true) {
        if(!initialState->isFinalState()) {
            if(!initialState->getWhichPlayer()) {     
                while(true) {
                    cout << "\nOh Human, Enter Bin Choice (Must be between 0 - 5) : ";                
                    cin >> pp.second;
                    if(0 <= pp.second && pp.second < 6 && initialState->getStones(pp.second)) {
                        break;
                    }
                    else {
                        cout << "\n\nWrong Move Human\n\n";
                        initialState->printState();
                    }
                }                
                cout << "\nHuman picks bin no : " << pp.second << "\n\n";
            }
            else {
                W1 = weights[0][0]; W2 = weights[0][1]; W3 = weights[0][2]; W4 = weights[0][3];
                pp = p1.minimaxAlphaBetaPruning(initialState, 1, INT_MIN, INT_MAX, true);
                cout << "\nPlayer 1 (AI) picks bin no : " << pp.second << "\n\n";
            }
            initialState = initialState->changeState(pp.second);
            initialState->printState();
        }
        else {
            initialState->finalStoneCollection();
            cout << "\n\n=========FINAL STATE=========\n\n";
            initialState->printState();
            cout <<"\n\n";
            if(initialState->getWinner() == 1) {
                cout << "Player 1 (AI) has won\n\n";
            }
            else if(initialState->getWinner() == 2) {
                cout << "Draw\n\n";
            }
            else {             
                cout << "Human has won\n\n";
            }
            break;
        }   
    }

    delete initialState;
}

void Play_HUMAN_vs_HUMAN() {


    bool startingPlayer;

    cout << "Enter Starting Player ID (Must be 0 or 1) : ";
    cin >> startingPlayer;
    cout << '\n';

    Player p0(0, 0, 0);
    Player p1(1, 0, 0);


    GameState *initialState = GameState::getInitialState(startingPlayer);;
    pair<int, int> pp;

 
    initialState->printState();

    while(true) {
        if(!initialState->isFinalState()) {
            if(!initialState->getWhichPlayer()) {     
                while(true) {
                    cout << "\nOh Human0, Enter Bin Choice (Must be between 0 - 5) : ";                
                    cin >> pp.second;
                    if(0 <= pp.second && pp.second < 6 && initialState->getStones(pp.second)) {
                        break;
                    }
                    else {
                        cout << "\n\nWrong Move Human0\n\n";
                        initialState->printState();
                    }
                }                
                cout << "\nHuman0 picks bin no : " << pp.second << "\n\n";
            }
            else {
               while(true) {
                    cout << "\nOh Human1, Enter Bin Choice (Must be between 7 - 12) : ";                
                    cin >> pp.second;
                    if(7 <= pp.second && pp.second < 13 && initialState->getStones(pp.second)) {
                        break;
                    }
                    else {
                        cout << "\n\nWrong Move Human1\n\n";
                        initialState->printState();
                    }
                }                
                cout << "\nHuman1 picks bin no : " << pp.second << "\n\n";
            }
            initialState = initialState->changeState(pp.second);
            initialState->printState();
        }
        else {
            initialState->finalStoneCollection();
            cout << "\n\n=========FINAL STATE=========\n\n";
            initialState->printState();
            cout <<"\n\n";
            if(initialState->getWinner() == 1) {
                cout << "Human1 has won\n\n";
            }
            else if(initialState->getWinner() == 2) {
                cout << "Draw\n\n";
            }
            else {             
                cout << "Human0 has won\n\n";
            }
            break;
        }   
    }

    delete initialState;
}

void generateReport() {
    ofstream report;
    report.open("report.csv");
    report << "Depth,Player0_Heuristic,Player1_Heuristic,Player0_Win,Player1_Win,Draw\n";

    const int maxHeuristicID = sizeof(heuristicsArr) / sizeof(heuristicsArr[0]);

    random_device device;
    mt19937 generator(device());
    uniform_int_distribution<int> distribution(60, 100);
    uniform_int_distribution<int> distribution_bool(0, 1);

    for(int depth = 1; depth < 4; depth++) {
        for(int p0_heuristic = 0; p0_heuristic < maxHeuristicID; p0_heuristic++) {
            for(int p1_heuristic = 0; p1_heuristic < maxHeuristicID; p1_heuristic++) {
                int p0_win = 0, p1_win = 0, draw = 0;
                for(int game = 0; game < 100; game++) {
                    int weights[2][4];
                    bool startingPlayer = distribution_bool(generator);

                    for(int i = 0; i < 4; i++) {
                        weights[0][i] = distribution(generator);
                        weights[1][i] = distribution(generator);
                    }
                                
                    Player p0(0, depth, p0_heuristic);
                    Player p1(1, depth, p1_heuristic);


                    GameState *initialState = GameState::getInitialState(startingPlayer);;
                    pair<int, int> pp;

                    while(true) {
                        if(!initialState->isFinalState()) {
                            if(!initialState->getWhichPlayer()) {
                                W1 = weights[0][0]; W2 = weights[0][1]; W3 = weights[0][2]; W4 = weights[0][3];
                                pp = p0.minimaxAlphaBetaPruning(initialState, 0, INT_MIN, INT_MAX, true);
                            }
                            else {
                                W1 = weights[1][0]; W2 = weights[1][1]; W3 = weights[1][2]; W4 = weights[1][3];
                                pp = p1.minimaxAlphaBetaPruning(initialState, 1, INT_MIN, INT_MAX, true);
                            }
                            initialState = initialState->changeState(pp.second);                    
                        }
                        else {
                            initialState->finalStoneCollection();                            
                            if(initialState->getWinner() == 1) {
                                p1_win++;
                            }
                            else if(initialState->getWinner() == 2) {
                                draw++;
                            }
                            else {             
                                p0_win++;
                            }
                            break;
                        }   
                    }

                    delete initialState;
                }
                report << depth << ',' << p0_heuristic << ',' << p1_heuristic << ',' << p0_win << ',' << p1_win << ',' << draw << '\n';
            }
        }
    }

    cout << "========DONE========\n";
    report.close();
}