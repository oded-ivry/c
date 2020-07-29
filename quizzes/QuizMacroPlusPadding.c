#define OFFESET(s,f) (size_t)(&(s*)0->f)

#define TO_LOWER(x) ((x>='A') && (x<='Z') ? (x+32) : x)

#define MAX(a,b) ((a > b) ? a : b))

#define MAX3(a,b,c) (((a > b) && (a > c)) ? a : ((b > c) ? b : c))

#define IS_UNSINGNEDNUMBER(x) ((x>0)&&(~x>0))
