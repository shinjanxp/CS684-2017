//  Automatically generated by /home/shinjan/.opam/4.05.0/bin/rdbg-batch version "1.39" ("aeef312")
//  on shinjan-hp-x360 the 20/2/2018 at 21:54:18
// rdbg-batch -o luciole.rif -lurette -l 1000 --sut-stdio lus2lic mealy.lus -node mealy -exec -rif

/* droconf.h begins */
/*
Struct necessary for building a DRO archive
(Dynamically linkable Reactive Object)
Such an archive can be loaded by simec/luciole
*/
#define DROVERSION "1.1"
#define xstr(s) str(s)  /* converts macro to string */
#define str(s) #s
/* should be of type type dro_desc_t */
#define DRO_DESC_NAME  dro_desc
struct dro_var_t {
	const char* ident;
	const char* type;
	void* valptr;
};

struct dro_desc_t {
	const char* version;
	const char* name;
	int nbins;
	struct dro_var_t* intab;
	int nbouts;
	struct dro_var_t* outab;
	int ( *step )();
	void ( *reset )();
	void ( *init )();
}; 
/* droconf.h ends */

#include "stdlib.h"
#include <stdio.h>
typedef int _bool;
typedef int _int;
typedef double _real;
struct _luciole_ctx {
// INPUTS
    _bool _input;
// OUTPUTS
    _bool _output;
    _int _state;
};
typedef struct _luciole_ctx luciole_ctx;
static luciole_ctx* _THIS = NULL;
/* Standard Input procedures **************/
_bool _get_bool(){
   char b[512];
   _bool r = 0;
   int s = 1;
   char c;
   do {
      if(scanf("%s", b)==EOF) exit(0);
      s = sscanf(b, "%c", &c);
      r = -1;
      if(c == 'q') exit(0);
      if((c == '0') || (c == 'f') || (c == 'F')) r = 0;
      if((c == '1') || (c == 't') || (c == 'T')) r = 1;
   } while((s != 1) || (r == -1));
   return r;
}
_int _get_int(){
   char b[512];
   _int r;
   int s = 1;
   char c;
   do {
      if(scanf("%s", b)==EOF) exit(0);
      s = sscanf(b, "%c", &c);
      if(c == 'q') exit(0);
      s = sscanf(b, "%d", &r);
   } while(s != 1);
   return r;
}
_real _get_real(){
   char b[512];
   _real r;
   int s = 1;
   char c;
   do {
      if(scanf("%s", b)==EOF) exit(0);
      s = sscanf(b, "%c", &c);
      if(c == 'q') exit(0);
      s = sscanf(b, "%lf", &r);
   } while(s != 1);
   return r;
}
/* Standard Output procedures **************/
void _put_bool(_bool _V){
   printf("%s\n", (_V)? "t" : "f");
}
void _put_int(_int _V){
   printf("%d\n", _V);
}
void _put_real(_real _V){
   printf("%f\n", _V);
}

int __do_step();
int internal_step(){
  return __do_step();
}
void __do_reset();
void internal_reset(){
  return __do_reset();
}
void __do_init();
void internal_init(){
  return __do_init();
}
// inputs array
struct dro_var_t _intab[] = {
   {"input", "bool", NULL},
}; 

// outputs array 
struct dro_var_t _outab[] = {
   {"output", "bool", NULL},
   {"state", "int", NULL},
};

// 
struct dro_desc_t DRO_DESC_NAME = {
   "1.1",
   "rdbg",
   1,
   _intab,
   2,
   _outab,
   internal_step,
   internal_reset,
   internal_init
};

int __do_step(){
if(_THIS) {
   _put_bool(_THIS->_input);
   fflush(stdout);
   _THIS->_output = _get_bool();
   _THIS->_state = _get_int();
   //always happy...
   return 0;
  } else {
    printf("initialisation problem\n");
    return 2;
 }
}
void __do_reset(){
  //reset or create
    if(_THIS) {
     // nop
    } else {
      __do_init();
    }
 }
void __do_init(){
// create
  _THIS = malloc(sizeof(luciole_ctx));
  _intab[0].valptr = (void*)(& _THIS->_input);
  _outab[0].valptr = (void*)(& _THIS->_output);
  _outab[1].valptr = (void*)(& _THIS->_state);
}
