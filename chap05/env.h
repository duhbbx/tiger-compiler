typedef struct E_enventry_ *E_enventry;

struct E_enventry_ {enum {E_varEnventry, E_funEntry} kind;
                    union {struct {Ty_ty ty;} var;
                           struct {Ty_tyList formals; Ty_ty result;} fun;
                         } u;
                  };

E_enventry E_VarEnventry(Ty_ty ty);
E_enventry E_FunEntry(Ty_tyList formals, Ty_ty result);

S_table E_base_tenv(void);  /* Ty_ty environment */
S_table E_base_venv(void);  /* E_enventry environment */