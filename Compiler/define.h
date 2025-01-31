#define FOR_EACH_TABLE(TABLE, TAR)                           \
	for ((TAR) = ((TABLE) == NULL) ? NULL : (TABLE)->target; \
		 (TAR) != NULL;                                      \
		 (TABLE) = (TABLE)->next, (TAR) = ((TABLE) == NULL) ? NULL : (TABLE)->target)
#define FOR_EACH_USE_TABLE(USE, STMT) \
	for ((STMT) = ((USE) == NULL) ? NULL : (USE)->stmt; (USE) != NULL; (USE) = (USE)->next, (STMT) = ((USE) == NULL) ? NULL : (USE)->stmt)

/*state*/
unsigned int POINTER_NOT_EXIST = 0;
unsigned int POINTER_STATE_IS_FREE = 1;
unsigned int POINTER_STATE_IS_NORMAL = 2;
unsigned int POINTER_STATE_IS_MALLOC = 3;
unsigned int POINTER_STATE_IS_FILE = 4;
unsigned int POINTER_STATE_MAY_IS_FREE = 5;

const unsigned int POINTER_NOT = 0;
const unsigned int POINTER_MAY = 1;
const unsigned int POINTER_MUST = 2;

unsigned int IS_MALLOC_FUCNTION = 1;

unsigned int IS_PTHREAD_FUCNTION = 3;
unsigned int IS_OTHRER_FUCNTION = 2;
unsigned int IS_HEAP_FUCNTION = -1;
unsigned int PTABLE_IS_NULL = -2;
unsigned int FUNCITON_THREAD = 666;
unsigned int FUNCITON_HEAP = 777;
unsigned int RET_HEAP_OBJECT = 888;
unsigned int EFFECTIVE = 10000;
unsigned int CREATE_JOINABLE = 0;
unsigned int CREATE_DETACHED = 1;
unsigned int DISABLE_TREACE = -100;
int GIMPLE_MALLOC_COUNT = 0;
int FUCNTION_RETURN_HEAP_OBJECT = 0;
int GIMPLE_FREE_COUNT = 0;
int debug_count=0;
/*dump file */
FILE *fp;

/*interprocedural analysis*/
bool ipa = true;
bool freeanysis = true; // no free no anysis
bool vscode_extensionmod = false;
bool vscode_extensionIgonefreemod = true;
bool defmemoryleak = true;
bool memoryleakcheck = true;
// Korea testcase need turn on
bool Looserulesfree = true;
bool useafterfree = false;
bool debugmod = false;
bool debugoutput = true;
bool threadmod = true;
bool relatemod = false;
bool freemod = true;
bool retmod = true;
bool pthread_detachedmod = false;
bool pthread_exitmod = false;
bool tracerelatestmt = true;
bool prebranchexit = false;
bool traceallfucntion =false;
bool retnotheapobjskipcheck=true;
bool stmtloopcheck = false;
bool samefucntioncheck = true;
bool maxbasicblockcalc = true;
bool pathconstraint = false;
bool contextsentive = true;
bool symbolicexecution = true;

/*allocation and deallocation table*/
struct ptb
{
	tree target;
	location_t loc;
	ptb *next;
	int state;
	bool may_realloc, is_phi_stmt;
	gimple *last_stmt, *dealloc_stmt;
	basic_block bb;
	cgraph_node *node;
	gimple *caller;
	function *fun;
	bool removed;
	bool inbranch;
	gimple *swap_stmt;
	tree swap_target = NULL;
	int swap_type = 0;
	int pthread_type = 0;
	int size = 0;
};

/*ptb declaration*/
ptb start1, start2, start3, start4, start5, start6, start7, start8, start9;
ptb *ptable, *retable, *ftable;
ptb *phitable, *return_table, *use_table, *fopen_table;
ptb *locktable;
ptb *unlocktable;
struct symbolicinfoPatharray
{
	// gimple *cond_stmt;
	basic_block bb;
	int boolt = 1;
};

struct breakpoint
{
	string name;
	int line;
};
struct symbolicinfo
{
	gimple *cond_stmt;
	gimple *switch_stmt;
	tree cond_rhs;
	tree cond_lhs;
	cgraph_node *node;
	vector<basic_block> switchs;
	basic_block cond_truebranch;
	basic_block cond_falsebranch;
	int prevlogic = 1;
	// tree symbolicExecutionPathConstraintNode;
	vector<basic_block> symbolicExecutionPathConstraint;
	vector<symbolicinfoPatharray> symbolicExecutionPathConstraintarrayTrue;
	vector<symbolicinfoPatharray> symbolicExecutionPathConstraintarrayFalse;
	// hash_map<basic_block, symbolicinfoPatharray> *syminfo;
};

struct gimple_array
{
	gimple *stmt;
	gimple *ret_stmt;
	tree aptr;
	tree target;
	gimple_array *next;
	int size = 0;
};

/*function decl tree and rhs tree*/
struct fdecl
{
	tree fndecl;
	tree fn;
};

/*function decl and location*/
struct var_points_to
{
	vector<vector<pair<fdecl, location_t>>> may_malloc_path;
	tree decl;
};

/*
int return_type
return type
normal 0
pointer 0
function pointer
*/
struct function_path
{
	cgraph_node *cgnext;
	tree prev;
	tree next;
};
struct return_type
{
	int return_type_stmt_num = 0;
	gimple *stmt;
	tree locfucntion;
	tree return_tree;
	char *name= "";
};
struct assign_type
{
	gimple *stmt;
	tree assign_tree;
	tree form_tree;
};

struct free_type
{
	gimple *stmt;
	tree free_tree;
	int Looserulesfree = 0;
};
static int alloc_index = -1;
struct basic_block_attributes
{
	int index;
	int mttindex;
	int has_stmt;
	int has_free;
	int has_exit;
	int num;
	gimple *stmt;
	basic_block bb;
	tree stmt_tree;
};

struct defmalloc_type
{
	gimple *stmt;
	tree malloc_tree;
	vector<free_type> free_array;
	// int Looserulesfree = 0;
};
struct relate_type
{
	gimple *stmt;
	gimple *laststmt;
	tree relate_tree;
	tree relate_funtree;
	unsigned int now_fucntion = 0;
	unsigned int now_stmt = 0;
	int now_basicblock = 0;
};

struct pthread_detched_type
{
	gimple *stmt;
	tree pthread_detched_tree;
};

struct pthread_exit_type
{
	gimple *stmt;
	tree pthread_exit_tree;
};

/*define return_type struct*/
struct function_return_array
{
	int return_type_num = 0;
	int pthread_type_num = -1;

	vector<return_type> return_type_array;
};

/*define return_type struct*/
struct function_path_array
{
	int funtion_type_num = 0;
	vector<function_path> function_path_array;
};

/*define assign_type struct*/
struct function_assign_array
{
	int pass = 0;
	vector<assign_type> assign_type_array;
};

/*define assign_type struct*/
struct pthread_attr_array
{
	gimple *stmt;
	tree attr_tree;
	int attr_type_num = 0;
};

/*define free_type struct*/
struct function_free_array
{
	vector<free_type> free_type_array;
};

/*define pthread_detched struct*/
struct function_pthread_detched_array
{
	vector<pthread_detched_type> pthread_detched_array;
};

/*define pthread_detched struct*/
struct function_pthread_exit_array
{
	vector<pthread_exit_type> pthread_exit_array;
};
struct function_graph_array
{
	// Graph graph_type_array;
	cgraph_node *graph_node;
};
/*define free_type struct*/
struct function_relate_array
{
	vector<relate_type> relate_type_array;
};

/*collect function return types */
hash_map<tree, function_return_array> *function_return_collect;
/*collect function var decl ssa name */
hash_map<tree, function_assign_array> *function_assign_collect;
/*collect function pthread attr */
hash_map<tree, pthread_attr_array> *pthread_attr_setdetachstates;
/*collect function pthread_detched */
hash_map<tree, function_pthread_detched_array> *function_pthread_detched_collect;
/*collect function pthread_exit */
hash_map<tree, function_pthread_exit_array> *function_pthread_exit_collect;
/*collect function path */
hash_map<tree, function_path_array> *function_path_collect;
/*collect function free */
hash_map<tree, function_free_array> *function_free_collect;
/*collect fucntion graph_array*/
hash_map<tree, function_graph_array> *function_graph_collect;
/*collect fucntion graph_array*/
hash_map<tree, function_relate_array> *function_relate_collect;

// /*collect fucntion maxbasicblock*/
// hash_map<tree, int> *function_maxbasicblock_collect;

/*record each DFS graph*/
// hash_map<cgraph_node *, Graph> *fDFS;

/*use function tree search cgraph_node*/
hash_map<tree, cgraph_node *> *fnode;

/*rhs function search function decl and location*/
hash_map<tree, var_points_to> *tvpt;
hash_map<tree, gimple_array> *treeGimpleArray;

/**/
hash_map<basic_block, symbolicinfo> *syminfo;
// hash_map<basic_block, basic_block_attributes> *bestfreepaths;
vector<basic_block_attributes> bestfreepaths;
// hash_map<gimple *, tree> *symbolicExecutionPathConstraintNode;

/*record each DFS graph*/
hash_map<cgraph_node *, Graph> *fDFS;

/*collect  function stack*/
class CStack : public std::stack<tree>
{
public:
	using std::stack<tree>::c; // expose the container
};
/*collect stmt stack*/
class CstmtStack : public std::stack<gimple *>
{
public:
	using std::stack<gimple *>::c; // expose the container
};

vector<gimple *> new_gimple_array;
vector<tree> new_gimpletree_array;
vector<basic_block> new_path_array;
vector<tree> traceStack;
vector<tree> pathStack;
vector<basic_block> symbolicExecution;
vector<basic_block> symbolicExecutionswitch;
vector<breakpoint> vbreakpoint;
vector<return_type> global_ret_type_array;

CStack stmtStack;
CstmtStack stmtStack2;

function *main_fun;

struct timespec Globaltime, Globaltimeend;
static gimple *now_stmt;
static int totalsize; //宣告一個整數型態size變數，用來儲存x的位元組大小
static int levelsize = 0;
static int pointtablecount = 0;
// static int levelsize = 0;
static tree now_tree;
static enum cdi_direction nowdir;
unsigned int SDBMHash(char *str);
tree prechecktree(tree tree);
void analyze_type(tree tree_typed);
int dump_points_to_solution2(FILE *file, struct pt_solution *pt);
void check_bbinfo(cgraph_node *m, basic_block bb);
void Checknew_search_imm_use_rhs(gimple_array *used_stmt, gimple *use_stmt, tree target, tree target2);
void Checknew_search_imm_use_lhs(gimple_array *used_stmt, gimple *use_stmt, tree target, tree target2);
int check_stmtStack4(gimple *stmt);
int check_stmtStack3(tree target);
int check_stmtStack2(gimple *stmt);
int check_stmtStack(tree target);

void printf_bbinfo(basic_block bb, int flag);
void set_PathConstraintarray(basic_block bb, int flag);
void set_bbinfo(basic_block bb);

int check_stmtStack(tree target);
void checkPointerConstraint(tree function_tree, ptb *ptable, gimple_array *user_tmp, tree checkTree, int threadcheck);
void record_fucntion(cgraph_node *node);

void collect_function_call(gimple *gc, cgraph_node *node, basic_block bb);
void collect_FunctionMapping_Assign(gimple *gc, cgraph_node *node, basic_block bb, ptb *ptable);

int trace_function_path(tree function_tree, int fucntion_level, tree mallocStmt_tree, int *freecount);
void walk_function_path(tree function_tree, int fucntion_level, ptb *ptable, gimple_array *user_tmp);
void tracefree_fucntion(cgraph_node *node, ptb *ptable, gimple_array *user_tmp);
void tracefree_fucntion(cgraph_node *node, ptb *ptable, gimple_array *user_tmp);

function_assign_array ret_function_varstmt(tree function_tree);
void collect_function_return(gimple *gc, cgraph_node *node, basic_block bb);
void collect_function_continue(gimple *gc, cgraph_node *node, basic_block bb);
void FunctionStmtMappingRet(ptb *ptable, ptb *ftable, gimple_array *user_tmp);
void FunctionStmtMappingAssign(ptb *ptable, gimple_array *user_tmp);

struct timespec diff(struct timespec start, struct timespec end);
int fprintf2(FILE *stream, const char *format, ...);
DEBUG_FUNCTION void debug_gimple_stmt2(gimple *gs);
DEBUG_FUNCTION void debug_tree2(tree node);
DEBUG_FUNCTION void debug2(const tree_node *ptr);
DEBUG_FUNCTION void debug2(gimple *ptr);
bool warning_at2(location_t location, int opt, const char *gmsgid, ...);
bool warning_at2(rich_location *richloc, int opt, const char *gmsgid, ...);


int update_basic_block(basic_block bb, int setmttindex, int sethas_stmt, int sethas_free, int sethas_exit);
void printfBasicblock();
void dump_fucntion(cgraph_node *node, ptb *ptable, gimple_array *user_tmp);
void new_search_imm_use(gimple_array *used_stmt, tree target, tree target2);
void Prenew_search_imm_use(gimple_array *used_stmt, tree target, tree target2);
void printfPointerConstraint(ptb *ptable, gimple_array *user_tmp);
void print_function_return(tree function_tree);
void print_function_return2(tree function_tree);
void trace_fucntion_relate_stmt(cgraph_node *node, tree function_tree, tree mallocStmt_tree);
void PointerConstraint(ptb *ptable, ptb *ftable);
