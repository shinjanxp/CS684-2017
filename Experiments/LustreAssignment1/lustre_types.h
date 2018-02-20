/* This file was generated by lus2lic version master.729 (da12cdfcb6fe6d1f6c4abb97c6b01e79465f3296). */
/*  lus2lic edge.lus -n edge -2c -cc */
/* on shinjan-hp-x360 the 19/02/2018 at 17:59:01 */

#ifndef _SOC2C_PREDEF_TYPES
#define _SOC2C_PREDEF_TYPES
typedef int _boolean;
typedef int _integer;
typedef char* _string;
typedef double _real;
typedef double _double;
typedef float _float;
#define _false 0
#define _true 1
#endif
// end of _SOC2C_PREDEF_TYPES
// User typedef 
#ifndef _edge_edge_TYPES
#define _edge_edge_TYPES
#endif // enf of  _edge_edge_TYPES
// Memoryless soc ctx typedef 
// Memoryfull soc ctx typedef 
/* Lustre_pre_ctx */
typedef struct {
   /*Memory cell*/
   _boolean _memory ;
} Lustre_pre_ctx_type;

/* Lustre_arrow_ctx */
typedef struct {
   /*Memory cell*/
   _boolean _memory ;
} Lustre_arrow_ctx_type;

/* edge_r_edge_ctx */
typedef struct {
   /*INSTANCES*/
   Lustre_pre_ctx_type Lustre_pre_ctx_tab[1];
   Lustre_arrow_ctx_type Lustre_arrow_ctx_tab[1];
} edge_r_edge_ctx_type;

/* edge_edge_ctx */
typedef struct {
   /*INSTANCES*/
   edge_r_edge_ctx_type edge_r_edge_ctx_tab[2];
} edge_edge_ctx_type;

