int grip = 1,thrust = 3,slash = 4,block = 5,parry = 7,movement = 8;
const char* p0result = "p0result";
const char* p1result = "p1result";
char p0input;
char p1input;
int p0pos = 2;
int p1pos = 6;
int p0stance ;
int p1stance ;
//player cmd numbers
//grip change >> stab >> slash >> block >> parry >>  move
//   0 >> 1 >>   2  >>   3   >>    4 u/d   >>  5  >> 6
int p0cmd ; //grip change >> stab >> slash >> move >> block >> parry
int p1cmd ;
int boardsize = 8;
int squaresize = 10;
int totalrows = 5;
char rows[5][80] ;
bool gameOn = TRUE;
//if a hit is scored mid round do not finish carrying out the actions inputed
bool roundOn = FALSE;
//specific images for clashes to prevent line spacing issues
//when an attack hits, blocked, parried, bumping heads?
bool clash = FALSE;
  WINDOW * win;
  int sign(int x);
void GameLoop();
void GripChange(int p0change,int p1change);
void ThrustAttack(int p0change,int p1change);
void SlashAttack(int p0change,int p1change);
void PlayerMove(int p0change,int p1change);
void ExecuteInputs(int p0action,int p1action);
void DrawBoard();
void PlacePlayerOne();
void PlacePlayerZero();
void ResetBoard();

int string_size(const char * str);
