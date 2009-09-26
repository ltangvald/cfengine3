/* 
   Copyright (C) 2008 - Cfengine AS

   This file is part of Cfengine 3 - written and maintained by Cfengine AS.
 
   This program is free software; you can redistribute it and/or modify it
   under the terms of the GNU General Public License as published by the
   Free Software Foundation; either version 3, or (at your option) any
   later version. 
   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.
 
  You should have received a copy of the GNU General Public License
  
  along with this program; if not, write to the Free Software
  Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA

*/

/*****************************************************************************/
/*                                                                           */
/* File: prototypes3.h                                                       */
/*                                                                           */
/* Created: Sun Aug  5 13:43:56 2007                                         */
/*                                                                           */
/*****************************************************************************/

/* pub/full-write.c */

int cf_full_write (int desc, char *ptr, size_t len);

/* cflex.l */

int yylex (void);

/* cfparse.y */

void yyerror (char *s);
int yyparse (void);

/* Generic stubs for the agents */
    
void ThisAgentInit(void);
void KeepPromises(void);

/* agent.c */

int ScheduleAgentOperations(struct Bundle *bp);

/* agentdiagnostic.c */

void AgentDiagnostic(void);

/* args.c */

int MapBodyArgs(char *scopeid,struct Rlist *give,struct Rlist *take);
struct Rlist *NewExpArgs(struct FnCall *fp, struct Promise *pp);
void ArgTemplate(struct FnCall *fp,char **argtemplate, enum cfdatatype *argtypes,struct Rlist *finalargs);
void DeleteExpArgs(struct Rlist *args);

/* assoc.c */

struct CfAssoc *NewAssoc(char *lval,void *rval,char rtype,enum cfdatatype dt);
void DeleteAssoc(struct CfAssoc *ap);
struct CfAssoc *CopyAssoc(struct CfAssoc *old);
void ShowAssoc (struct CfAssoc *cp);
    
/* attributes.c */

struct Attributes GetFilesAttributes(struct Promise *pp);
struct Attributes GetReportsAttributes(struct Promise *pp);
struct Attributes GetExecAttributes(struct Promise *pp);
struct Attributes GetProcessAttributes(struct Promise *pp);
struct Attributes GetStorageAttributes(struct Promise *pp);
struct Attributes GetClassContextAttributes(struct Promise *pp);
struct Attributes GetTopicsAttributes(struct Promise *pp);
struct Attributes GetOccurrenceAttributes(struct Promise *pp);
struct Attributes GetPackageAttributes(struct Promise *pp);
struct Attributes GetMeasurementAttributes(struct Promise *pp);
struct Attributes GetDatabaseAttributes(struct Promise *pp);
    
struct Packages GetPackageConstraints(struct Promise *pp);
struct ExecContain GetExecContainConstraints(struct Promise *pp);
struct Recursion GetRecursionConstraints(struct Promise *pp);
struct FileSelect GetSelectConstraints(struct Promise *pp);
struct FilePerms GetPermissionConstraints(struct Promise *pp);
struct TransactionContext GetTransactionConstraints(struct Promise *pp);
struct DefineClasses GetClassDefinitionConstraints(struct Promise *pp);
struct FileRename GetRenameConstraints(struct Promise *pp);
struct FileDelete GetDeleteConstraints(struct Promise *pp);
struct FileChange GetChangeMgtConstraints(struct Promise *pp);
struct FileCopy GetCopyConstraints(struct Promise *pp);
struct FileLink GetLinkConstraints(struct Promise *pp);
struct Context GetContextConstraints(struct Promise *pp);
struct ProcessSelect GetProcessFilterConstraints(struct Promise *pp);
struct ProcessCount GetMatchesConstraints(struct Promise *pp);
struct EditDefaults GetEditDefaults(struct Promise *pp);
struct Attributes GetMethodAttributes(struct Promise *pp);
struct Attributes GetInterfacesAttributes(struct Promise *pp);
struct Attributes GetInsertionAttributes(struct Promise *pp);
struct EditLocation GetLocationAttributes(struct Promise *pp);
struct Attributes GetDeletionAttributes(struct Promise *pp);
struct Attributes GetColumnAttributes(struct Promise *pp);
struct Attributes GetReplaceAttributes(struct Promise *pp);
struct EditRegion GetRegionConstraints(struct Promise *pp);
struct EditReplace GetReplaceConstraints(struct Promise *pp);
struct EditColumn GetColumnConstraints(struct Promise *pp);
struct TopicAssociation GetAssociationConstraints(struct Promise *pp);
struct StorageMount GetMountConstraints(struct Promise *pp);
struct StorageVolume GetVolumeConstraints(struct Promise *pp);
struct CfTcpIp GetTCPIPAttributes(struct Promise *pp);
struct Report GetReportConstraints(struct Promise *pp);
struct LineSelect GetInsertSelectConstraints(struct Promise *pp);
struct LineSelect GetDeleteSelectConstraints(struct Promise *pp);
struct Measurement GetMeasurementConstraint(struct Promise *pp);
struct CfACL GetAclConstraints(struct Promise *pp);
struct CfDatabase GetDatabaseConstraints(struct Promise *pp);

void ShowAttributes(struct Attributes a);

/* cfpromises.c */

void SetAuditVersion(void);
void VerifyPromises(enum cfagenttype ag);
void CompilePromises(void);

/* cfstreams.c */

void CfFOut(char *filename,enum cfreport level,char *errstr,char *fmt, ...);
void CfOut(enum cfreport level,char *errstr,char *fmt, ...);
void cfPS(enum cfreport level,char status,char *errstr,struct Promise *pp,struct Attributes attr,char *fmt, ...);
void CfFile(FILE *fp,char *fmt, ...);
void MakeLog(struct Item *mess,enum cfreport level);
void MakeReport(struct Item *mess,int prefix);
void FileReport(struct Item *mess,int prefix,char *filename);
void SanitizeBuffer(char *buffer);

/* cf_sql.c */

int CfConnectDB(CfdbConn *cfdb,enum cfdbtype dbtype,char *remotehost,char *dbuser, char *passwd, char *db);
void CfCloseDB(CfdbConn *cfdb);
void CfVoidQueryDB(CfdbConn *cfdb,char *query);
void CfNewQueryDB(CfdbConn *cfdb,char *query);
char **CfFetchRow(CfdbConn *cfdb);
char *CfFetchColumn(CfdbConn *cfdb,int col);
void CfDeleteQuery(CfdbConn *cfdb);
char *EscapeSQL(CfdbConn *cfdb,char *query);

/* client_code.c */

void DetermineCfenginePort(void);
struct cfagent_connection *NewServerConnection(struct Attributes attr,struct Promise *pp);
struct cfagent_connection *ServerConnection(char *server,struct Attributes attr,struct Promise *pp);
void ServerDisconnection(struct cfagent_connection *conn);
int cf_remote_stat(char *file,struct stat *buf,char *stattype,struct Attributes attr,struct Promise *pp);
CFDIR *cf_remote_opendir(char *dirname,struct Attributes attr,struct Promise *pp);
void NewClientCache(struct cfstat *data,struct Promise *pp);
void DeleteClientCache(struct Attributes attr,struct Promise *pp);
int CompareHashNet(char *file1,char *file2,struct Attributes attr,struct Promise *pp);
int CopyRegularFileNet(char *source,char *new,off_t size,struct Attributes attr,struct Promise *pp);
int ServerConnect(struct cfagent_connection *conn,char *host,struct Attributes attr, struct Promise *pp);
int CacheStat(char *file,struct stat *statbuf,char *stattype,struct Attributes attr,struct Promise *pp);
void FlushFileStream(int sd,int toget);
int ServerOffline(char *server);
struct cfagent_connection *ServerConnectionReady(char *server);
void MarkServerOffline(char *server);
void CacheServerConnection(struct cfagent_connection *conn,char *server);
void ServerNotBusy(struct cfagent_connection *conn);

/* client_protocols.c */

int IdentifyAgent(int sd,char *localip,int family);
int AuthenticateAgent(struct cfagent_connection *conn,struct Attributes attr,struct Promise *pp);
void CheckServerVersion(struct cfagent_connection *conn,struct Attributes attr, struct Promise *pp);
void SetSessionKey(struct cfagent_connection *conn);
int BadProtoReply(char *buf);
int OKProtoReply(char *buf);
int FailedProtoReply(char *buf);


/* chflags.c */

int ParseFlagString (struct Rlist *flags, u_long *plusmask, u_long *minusmask);
u_long ConvertBSDBits(char *s);

/* communication.c */

struct cfagent_connection *NewAgentConn(void);
void DeleteAgentConn(struct cfagent_connection *ap);
void DePort(char *address);
int IsIPV6Address(char *name);
int IsIPV4Address(char *name);
char *Hostname2IPString(char *hostname);
char *IPString2Hostname(char *ipaddress);
char *IPString2UQHostname(char *ipaddress);

/* comparray.c */

int FixCompressedArrayValue (int i, char *value, struct CompressedArray **start);
void DeleteCompressedArray (struct CompressedArray *start);
int CompressedArrayElementExists (struct CompressedArray *start, int key);
char *CompressedArrayValue (struct CompressedArray *start, int key);

/* constraints.c */

struct Constraint *AppendConstraint(struct Constraint **conlist,char *lval, void *rval, char type,char *classes);
void DeleteConstraintList(struct Constraint *conlist);
void *GetConstraint(char *lval,struct Constraint *list,char type);
int GetBooleanConstraint(char *lval,struct Constraint *list);
int GetIntConstraint(char *lval,struct Constraint *list);
double GetRealConstraint(char *lval,struct Constraint *list);
mode_t GetOctalConstraint(char *lval,struct Constraint *list);
uid_t GetUidConstraint(char *lval,struct Constraint *list,struct Promise *pp);
gid_t GetGidConstraint(char *lval,struct Constraint *list,struct Promise *pp);
struct Rlist *GetListConstraint(char *lval,struct Constraint *list);
void ReCheckAllConstraints(struct Promise *pp);
void PostCheckConstraint(char *type,char *bundle,char *lval,void *rval,char rvaltype);
int GetBundleConstraint(char *lval,struct Constraint *list);
int VerifyConstraintName(char *lval);
struct PromiseIdent *NewPromiseId(char *handle,struct Promise *pp);
struct PromiseIdent *PromiseIdExists(char *handle);

/* conversion.c */

long Months2Seconds(int m);
enum cfinterval Str2Interval(char *s);
enum cfdbtype Str2dbType(char *s);
char *Rlist2String(struct Rlist *list,char *sep);
int Signal2Int(char *s);
enum cfreport String2ReportLevel(char *typestr);
enum cfhashes String2HashType(char *typestr);
enum cfcomparison String2Comparison(char *s);
enum cflinktype String2LinkType(char *s);
enum cfdatatype Typename2Datatype(char *name);
enum cfdatatype GetControlDatatype(char *varname,struct BodySyntax *bp);
enum cfagenttype Agent2Type(char *name);
enum cfsbundle Type2Cfs(char *name);
enum representations String2Representation(char *s);
int GetBoolean(char *val);
long Str2Int(char *s);
long TimeCounter2Int(char *s);
long TimeAbs2Int(char *s);
mode_t Str2Mode(char *s);
int Str2Double(char *s);
void IntRange2Int(char *intrange,long *min,long *max,struct Promise *pp);
struct UidList *Rlist2UidList(struct Rlist *uidnames, struct Promise *pp);
struct GidList *Rlist2GidList(struct Rlist *gidnames, struct Promise *pp);
uid_t Str2Uid(char *uidbuff,char *copy,struct Promise *pp);
gid_t Str2Gid(char *gidbuff,char *copy,struct Promise *pp);
int Month2Int(char *string);
char *GetArg0(char *execstr);
void CommPrefix(char *execstr,char *comm);
int NonEmptyLine(char *s);
int Day2Number(char *datestring);
enum action_policy Str2ActionPolicy(char *s);
enum version_cmp Str2PackageSelect(char *s);
enum package_actions Str2PackageAction(char *s);
enum cf_acl_method Str2AclMethod(char *string);
enum cf_acl_type Str2AclType(char *string);
enum cf_acl_inherit Str2AclInherit(char *string);

/* crypto.c */

void DebugBinOut(char *buffer,int len);
void RandomSeed (void);
void LoadSecretKeys (void);
void MD5Random (unsigned char digest[EVP_MAX_MD_SIZE+1]);
int EncryptString (char *in, char *out, unsigned char *key, int len);
int DecryptString (char *in, char *out, unsigned char *key, int len);
RSA *HavePublicKey (char *ipaddress);
void SavePublicKey (char *ipaddress, RSA *key);
void DeletePublicKey (char *ipaddress);
void GenerateRandomSessionKey (void);
char *KeyPrint(RSA *key);

/* dtypes.c */

int IsSocketType(char *s);
int IsTCPType(char *s);
int IsProcessType(char *s);

/* enterprise_stubs.c */

void Aggregate(void);
void SetPolicyServer(char *name);
int IsEnterprise(void);
void EnterpriseVersion(void);
void EnterpriseContext(void);
char *GetProcessOptions(void);
int EnterpriseExpiry(char *day,char *month,char *year);
char *GetConsolePrefix(void);
char *MailSubject(void);
void CheckAutoBootstrap(void);
pid_t StartTwin(int argc,char **argv);
void SignalTwin(void);
void InitMeasurements(void);
void BundleNode(FILE *fp,char *bundle);
void BodyNode(FILE *fp,char *bundle,int call);
void TypeNode(FILE *fp,char *type);
void PromiseNode(FILE *fp,struct Promise *pp,int type);
void RegisterBundleDependence(char *absscope,struct Promise *pp);
void MapPromiseToTopic(FILE *fp,struct Promise *pp,char *version);
void Nova_MapPromiseToTopic(FILE *fp,struct Promise *pp,char *version);
void ShowTopicRepresentation(FILE *fp);
void PreSanitizePromise(struct Promise *pp);
void Nova_ShowTopicRepresentation(FILE *fp);
void NotePromiseConditionals(struct Promise *pp);
void DependencyGraph(struct Topic *map);
void HistoryUpdate(struct Averages newvals);
void GetClassName(int i,char *name);
void LookUpClassName(int i,char *name);
void SummarizeCompliance(int xml,int html,int csv,int embed,char *stylesheet,char *head,char *foot,char *web);
void SummarizePerPromiseCompliance(int xml,int html,int csv,int embed,char *stylesheet,char *head,char *foot,char *web);
void SummarizeSetuid(int xml,int html,int csv,int embed,char *stylesheet,char *head,char *foot,char *web);
void SummarizeFileChanges(int xml,int html,int csv,int embed,char *stylesheet,char *head,char *foot,char *web);
void VerifyMeasurement(double *this,struct Attributes a,struct Promise *pp);
void SetMeasurementPromises(struct Item **classlist);
void LongHaul(void);
void VerifyACL(char *file,struct Attributes a, struct Promise *pp);
int CheckACLSyntax(char *file,struct CfACL acl,struct Promise *pp);
int CfVerifyTablePromise(CfdbConn *cfdb,char *name,struct Rlist *columns,struct Attributes a,struct Promise *pp);
int VerifyDatabasePromise(CfdbConn *cfdb,char *database,struct Attributes a,struct Promise *pp);
int VerifyTablePromise(CfdbConn *cfdb,char *table,struct Rlist *columns,struct Attributes a,struct Promise *pp);
void ReportSoftware(struct CfPackageManager *list);
void ReportPatches(struct CfPackageManager *list);
void SummarizeSoftware(int xml,int html,int csv,int embed,char *stylesheet,char *head,char *foot,char *web);
void SummarizeUpdates(int xml,int html,int csv,int embed,char *stylesheet,char *head,char *foot,char *web);
void LoadSlowlyVaryingObservations(void);
void RegisterLiteralServerData(char *handle,struct Promise *pp);
char *ReturnLiteralData(char *handle);
char *GetRemoteScalar(char *handle,char *server,int encrypted);
char *PromiseID(struct Promise *pp);
void NotePromiseCompliance(struct Promise *pp,double val);
time_t GetPromiseCompliance(struct Promise *pp,double *value,double *average,double *var,time_t *lastseen);
void SyntaxCompletion(char *s);
int GetRegistryValue(char *key,char *value,char *buffer);
void NoteVarUsage(void);
void SummarizeVariables(int xml,int html,int csv,int embed,char *stylesheet,char *head,char *foot,char *web);
void CSV2XML(struct Rlist *list);
void *CfLDAPValue(char *uri,char *dn,char *filter,char *name,char *scope,char *sec);
void *CfLDAPList(char *uri,char *dn,char *filter,char *name,char *scope,char *sec);
void *CfLDAPArray(char *array,char *uri,char *dn,char *filter,char *scope,char *sec);
void *CfRegLDAP(char *uri,char *dn,char *filter,char *name,char *scope,char *regex,char *sec);
void CacheUnreliableValue(char *caller,char *handle,char *buffer);
int RetrieveUnreliableValue(char *caller,char *handle,char *buffer);
void ReviveOther(int argc,char **argv);
void GrandSummary(void);

/* env_context.c */

int Abort(void);
int ValidClassName(char *name);
void KeepClassContextPromise(struct Promise *pp);
int ContextSanityCheck(struct Attributes a);
void PushPrivateClassContext(void);
void PopPrivateClassContext(void);
void DeletePrivateClassContext(void);
void DeleteEntireHeap(void);
void NewPersistentContext(char *name,unsigned int ttl_minutes,enum statepolicy policy);
void DeletePersistentContext(char *name);
void LoadPersistentContext(void);
int EvalClassExpression(struct Constraint *cp,struct Promise *pp);
void AddEphemeralClasses(struct Rlist *classlist);
void NewClass(char *class);
void NewBundleClass(char *class,char *bundle);
void DeleteClass(char *class);
int VarClassExcluded(struct Promise *pp,char **classes);
void NewClassesFromString(char *classlist);
void NegateClassesFromString(char *class,struct Item **heap);
void AddPrefixedClasses(char *name,char *classlist);
void NewPrefixedClasses(char *name,char *classlist);
int IsHardClass (char *sp);
int IsSpecialClass (char *class);
int IsExcluded (char *exception);
int IsDefinedClass (char *class);
int EvaluateORString (char *class, struct Item *list,int fromIsInstallable);
int EvaluateANDString (char *class, struct Item *list,int fromIsInstallable);
int GetORAtom (char *start, char *buffer);
int GetANDAtom (char *start, char *buffer);
int CountEvalAtoms (char *class);
int IsBracketed (char *s);
void SaveClassEnvironment(void);

/* evalfunction.c */

struct Rval FnCallSplayClass(struct FnCall *fp,struct Rlist *finalargs);
struct Rval FnCallRandomInt(struct FnCall *fp,struct Rlist *finalargs);
struct Rval FnCallGetUid(struct FnCall *fp,struct Rlist *finalargs);
struct Rval FnCallGetGid(struct FnCall *fp,struct Rlist *finalargs);
struct Rval FnCallExecResult(struct FnCall *fp,struct Rlist *finalargs);
struct Rval FnCallReadTcp(struct FnCall *fp,struct Rlist *finalargs);
struct Rval FnCallSelectServers(struct FnCall *fp,struct Rlist *finalargs);
struct Rval FnCallReturnsZero(struct FnCall *fp,struct Rlist *finalargs);
struct Rval FnCallIsNewerThan(struct FnCall *fp,struct Rlist *finalargs);
struct Rval FnCallIsAccessedBefore(struct FnCall *fp,struct Rlist *finalargs);
struct Rval FnCallIsChangedBefore(struct FnCall *fp,struct Rlist *finalargs);
struct Rval FnCallStatInfo(struct FnCall *fp,struct Rlist *finalargs,enum fncalltype fn);
struct Rval FnCallIPRange(struct FnCall *fp,struct Rlist *finalargs);
struct Rval FnCallHostRange(struct FnCall *fp,struct Rlist *finalargs);
struct Rval FnCallIsVariable(struct FnCall *fp,struct Rlist *finalargs);
struct Rval FnCallStrCmp(struct FnCall *fp,struct Rlist *finalargs);
struct Rval FnCallRegCmp(struct FnCall *fp,struct Rlist *finalargs);
struct Rval FnCallRegList(struct FnCall *fp,struct Rlist *finalargs);
struct Rval FnCallRegArray(struct FnCall *fp,struct Rlist *finalargs);
struct Rval FnCallGetIndices(struct FnCall *fp,struct Rlist *finalargs);
struct Rval FnCallGreaterThan(struct FnCall *fp,struct Rlist *finalargs,char c);
struct Rval FnCallUserExists(struct FnCall *fp,struct Rlist *finalargs);
struct Rval FnCallGroupExists(struct FnCall *fp,struct Rlist *finalargs);
struct Rval FnCallIRange(struct FnCall *fp,struct Rlist *finalargs);
struct Rval FnCallRRange(struct FnCall *fp,struct Rlist *finalargs);
struct Rval FnCallOnDate(struct FnCall *fp,struct Rlist *finalargs);
struct Rval FnCallAgoDate(struct FnCall *fp,struct Rlist *finalargs);
struct Rval FnCallAccumulatedDate(struct FnCall *fp,struct Rlist *finalargs);
struct Rval FnCallNow(struct FnCall *fp,struct Rlist *finalargs);
struct Rval FnCallReadFile(struct FnCall *fp,struct Rlist *finalargs);
struct Rval FnCallReadStringList(struct FnCall *fp,struct Rlist *finalargs,enum cfdatatype type);
struct Rval FnCallReadStringArray(struct FnCall *fp,struct Rlist *finalargs,enum cfdatatype type);
struct Rval FnCallClassMatch(struct FnCall *fp,struct Rlist *finalargs);
struct Rval FnCallUseModule(struct FnCall *fp,struct Rlist *finalargs);
struct Rval FnCallHash(struct FnCall *fp,struct Rlist *finalargs);
struct Rval FnCallHashMatch(struct FnCall *fp,struct Rlist *finalargs);
struct Rval FnCallCanonify(struct FnCall *fp,struct Rlist *finalargs);
struct Rval FnCallRegLine(struct FnCall *fp,struct Rlist *finalargs);
struct Rval FnCallSplitString(struct FnCall *fp,struct Rlist *finalargs);
struct Rval FnCallHostInNetgroup(struct FnCall *fp,struct Rlist *finalargs);
struct Rval FnCallClassify(struct FnCall *fp,struct Rlist *finalargs);
struct Rval FnCallRemoteScalar(struct FnCall *fp,struct Rlist *finalargs);
struct Rval FnCallRegLDAP(struct FnCall *fp,struct Rlist *finalargs);
struct Rval FnCallLDAPValue(struct FnCall *fp,struct Rlist *finalargs);
struct Rval FnCallLDAPList(struct FnCall *fp,struct Rlist *finalargs);
struct Rval FnCallLDAPArray(struct FnCall *fp,struct Rlist *finalargs);
struct Rval FnCallPeers(struct FnCall *fp,struct Rlist *finalargs);
struct Rval FnCallPeerLeader(struct FnCall *fp,struct Rlist *finalargs);
struct Rval FnCallPeerLeaders(struct FnCall *fp,struct Rlist *finalargs);
struct Rval FnCallRegistryValue(struct FnCall *fp,struct Rlist *finalargs);
struct Rval FnCallLastNode(struct FnCall *fp,struct Rlist *finalargs);
struct Rval FnCallFileSexist(struct FnCall *fp,struct Rlist *finalargs);

void *CfReadFile(char *filename,int maxsize);
char *StripPatterns(char *file_buffer,char *pattern);
void CloseStringHole(char *s,int start,int end);
int BuildLineArray(char *array_lval,char *file_buffer,char *split,int maxent,enum cfdatatype type);
int ExecModule(char *command);
void ModuleProtocol(char *command,char *line,int print);
int CheckID(char *id);

/* expand.c */

void ExpandPromise(enum cfagenttype ag,char *scopeid,struct Promise *pp,void *fnptr);
void ExpandPromiseAndDo(enum cfagenttype ag,char *scope,struct Promise *p,struct Rlist *scalarvars,struct Rlist *listvars,void (*fnptr)());
struct Rval ExpandDanglers(char *scope,struct Rval rval,struct Promise *pp);
void ScanRval(char *scope,struct Rlist **los,struct Rlist **lol,void *string,char type,struct Promise *pp);
void ScanScalar(char *scope,struct Rlist **los,struct Rlist **lol,char *string,int level,struct Promise *pp);

int IsExpandable(char *str);
int ExpandScalar(char *string,char buffer[CF_EXPANDSIZE]);
int ExpandPrivateScalar(char *contextid,char *string,char buffer[CF_EXPANDSIZE]);
struct Rval ExpandBundleReference(char *scopeid,void *rval,char type);
struct FnCall *ExpandFnCall(char *contextid,struct FnCall *f,int expandnaked);
struct Rval ExpandPrivateRval(char *contextid,void *rval,char type);
struct Rlist *ExpandList(char *scopeid,struct Rlist *list,int expandnaked);
struct Rval EvaluateFinalRval(char *scopeid,void *rval,char rtype,int forcelist,struct Promise *pp);
int IsNakedVar(char *str,char vtype);
void GetNaked(char *s1, char *s2);
void ConvergeVarHashPromise(char *scope,struct Promise *pp,int checkdup);
void ConvergePromiseValues(struct Promise *pp);
int Epimenides(char *var,char *rval,char rtype,int level);

/* exec_tool.c */

int IsExecutable(char *file);
int ShellCommandReturnsZero(char *comm,int useshell);
int GetExecOutput(char *command,char *buffer,int useshell);
void ActAsDaemon(int preserve);
char *WinEscapeCommand(char *s);

/* files_copy.c */

void *CopyFileSources(char *destination,struct Attributes attr,struct Promise *pp);
int CopyRegularFileDisk(char *source,char *new,struct Attributes attr,struct Promise *pp);
void CheckForFileHoles(struct stat *sstat,struct Attributes attr,struct Promise *pp);
int FSWrite(char *new,int dd,char *buf,int towrite,int *last_write_made_hole,int n_read,struct Attributes attr,struct Promise *pp);

/* files_edit.c */

struct edit_context *NewEditContext(char *filename,struct Attributes a,struct Promise *pp);
void FinishEditContext(struct edit_context *ec,struct Attributes a,struct Promise *pp);
int LoadFileAsItemList(struct Item **liststart,char *file,struct Attributes a,struct Promise *pp);
int SaveItemListAsFile(struct Item *liststart,char *file,struct Attributes a,struct Promise *pp);

/* files_editline.c */

int ScheduleEditLineOperations(char *filename,struct Bundle *bp,struct Attributes a,struct Promise *pp);
void KeepEditLinePromise(struct Promise *pp);
void VerifyLineDeletions(struct Promise *pp);
void VerifyColumnEdits(struct Promise *pp);
void VerifyPatterns(struct Promise *pp);
void VerifyLineInsertions(struct Promise *pp);
int InsertMissingLinesToRegion(struct Item **start,struct Item *begin_ptr,struct Item *end_ptr,struct Attributes a,struct Promise *pp);
int InsertMissingLinesAtLocation(struct Item **start,struct Item *begin_ptr,struct Item *end_ptr,struct Item *location,struct Item *prev,struct Attributes a,struct Promise *pp);
int DeletePromisedLinesMatching(struct Item **start,struct Item *begin,struct Item *end,struct Attributes a,struct Promise *pp);
int InsertMissingLineAtLocation(char *newline,struct Item **start,struct Item *location,struct Item *prev,struct Attributes a,struct Promise *pp);
int ReplacePatterns(struct Item *start,struct Item *end,struct Attributes a,struct Promise *pp);
int EditColumns(struct Item *file_start,struct Item *file_end,struct Attributes a,struct Promise *pp);
int EditLineByColumn(struct Rlist **columns,struct Attributes a,struct Promise *pp);
int EditColumn(struct Rlist **columns,struct Attributes a,struct Promise *pp);
int SanityCheckInsertions(struct Attributes a);
int SelectLine(char *line,struct Attributes a,struct Promise *pp);

/* files_links.c */

int VerifyLink(char *destination,char *source,struct Attributes attr,struct Promise *pp);
int VerifyAbsoluteLink(char *destination,char *source,struct Attributes attr,struct Promise *pp);
int VerifyRelativeLink(char *destination,char *source,struct Attributes attr,struct Promise *pp);
int VerifyHardLink(char *destination,char *source,struct Attributes attr,struct Promise *pp);
int KillGhostLink(char *name,struct Attributes attr,struct Promise *pp);
int MakeLink (char *from,char *to,struct Attributes attr,struct Promise *pp);
int MakeHardLink (char *from,char *to,struct Attributes attr,struct Promise *pp);
char *AbsLinkPath (char *from,char *relto);
int ExpandLinks(char *dest,char *from,int level);

/* files_hashes.c */

int Hash(char *name);
int ElfHash(char *key);

int FileHashChanged(char *filename,unsigned char digest[EVP_MAX_MD_SIZE+1],int warnlevel,enum cfhashes type,struct Attributes attr,struct Promise *pp);
void PurgeHashes(struct Attributes attr,struct Promise *pp);
int ReadHash(DB *dbp,enum cfhashes type,char *name,unsigned char digest[EVP_MAX_MD_SIZE+1], unsigned char *attr);
int WriteHash(DB *dbp,enum cfhashes type,char *name,unsigned char digest[EVP_MAX_MD_SIZE+1], unsigned char *attr);
void DeleteHash(DB *dbp,enum cfhashes type,char *name);
DBT *NewHashKey(char type,char *name);
void DeleteHashKey(DBT *key);
DBT *NewHashValue(unsigned char digest[EVP_MAX_MD_SIZE+1],unsigned char attr[EVP_MAX_MD_SIZE+1]);
void DeleteHashValue(DBT *value);

int CompareFileHashes(char *file1,char *file2,struct stat *sstat,struct stat *dstat,struct Attributes attr,struct Promise *pp);
int CompareBinaryFiles(char *file1,char *file2,struct stat *sstat,struct stat *dstat,struct Attributes attr,struct Promise *pp);
void HashFile(char *filename,unsigned char digest[EVP_MAX_MD_SIZE+1],enum cfhashes type);
void HashList(struct Item *list,unsigned char digest[EVP_MAX_MD_SIZE+1],enum cfhashes type);
void HashString(char *buffer,int len,unsigned char digest[EVP_MAX_MD_SIZE+1],enum cfhashes type);
int HashesMatch(unsigned char digest1[EVP_MAX_MD_SIZE+1],unsigned char digest2[EVP_MAX_MD_SIZE+1],enum cfhashes type);
char *HashPrint(enum cfhashes type,unsigned char digest[EVP_MAX_MD_SIZE+1]);
char *FileHashName(enum cfhashes id);
int FileHashSize(enum cfhashes id);

/* files_interfaces.c */

void SourceSearchAndCopy(char *from,char *to,int maxrecurse,struct Attributes attr,struct Promise *pp);
void VerifyCopy(char *source,char *destination,struct Attributes attr,struct Promise *pp);
void PurgeLocalFiles(struct Item *filelist,char *directory,struct Attributes attr,struct Promise *pp);
void CopyFile(char *sourcefile,char *destfile,struct stat sourcestatbuf,struct Attributes attr, struct Promise *pp);
int CompareForFileCopy(char *sourcefile,char *destfile,struct stat *ssb, struct stat *dsb,struct Attributes attr,struct Promise *pp);
void LinkCopy(char *sourcefile,char *destfile,struct stat *sb,struct Attributes attr, struct Promise *pp);
int cf_stat(char *file,struct stat *buf,struct Attributes attr, struct Promise *pp);
int cf_lstat(char *file,struct stat *buf,struct Attributes attr, struct Promise *pp);
int cf_readlink(char *sourcefile,char *linkbuf,int buffsize,struct Attributes attr, struct Promise *pp);
CFDIR *cf_opendir(char *name,struct Attributes attr, struct Promise *pp);
struct cfdirent *cf_readdir(CFDIR *cfdirh,struct Attributes attr, struct Promise *pp);
void cf_closedir(CFDIR *dirh);
int CopyRegularFile(char *source,char *dest,struct stat sstat,struct stat dstat,struct Attributes attr, struct Promise *pp);
void RegisterAHardLink(int i,char *value,struct Attributes attr, struct Promise *pp);
void FileAutoDefine(char *destfile);
int CfReadLine(char *buff,int size,FILE *fp);

/* files_names.c */

int IsDir(char *path);
int EmptyString(char *s);
int ExpandOverflow(char *str1,char *str2);
char *JoinPath(char *path,char *leaf);
char *JoinSuffix(char *path,char *leaf);
int IsAbsPath(char *path);
void AddSlash(char *str);
void DeleteSlash(char *str);
char *LastFileSeparator(char *str);
int ChopLastNode(char *str);
char *CanonifyName(char *str);
char *ReadLastNode(char *str);
int CompressPath(char *dest,char *src);
void Chop(char *str);
int IsIn(char c,char *str);
int IsAbsoluteFileName(char *f);
int RootDirLength(char *f);
char ToLower (char ch);
char ToUpper (char ch);
char *ToUpperStr (char *str);
char *ToLowerStr (char *str);

/* files_operators.c */

void TruncateFile(char *name);
int VerifyFileLeaf(char *path,struct stat *sb,struct Attributes attr,struct Promise *pp);
int CreateFile(char *file,struct Promise *pp,struct Attributes attr);
int ScheduleCopyOperation(char *destination,struct Attributes attr,struct Promise *pp);
int ScheduleLinkChildrenOperation(char *destination,struct Attributes attr,struct Promise *pp);
int ScheduleLinkOperation(char *destination,char *source,struct Attributes attr,struct Promise *pp);
int ScheduleEditOperation(char *filename,struct Attributes attr,struct Promise *pp);
struct FileCopy *NewFileCopy(struct Promise *pp);
void DeleteFileCopy(struct FileCopy *fcp);
void VerifyFileAttributes(char *file,struct stat *dstat,struct Attributes attr,struct Promise *pp);
void VerifyFileIntegrity(char *file,struct Promise *pp,struct Attributes attr);
int VerifyOwner(char *file,struct Promise *pp,struct Attributes attr,struct stat *statbuf);
void VerifyCopiedFileAttributes(char *file,struct stat *dstat,struct stat *sstat,struct Attributes attr,struct Promise *pp);
void VerifySetUidGid(char *file,struct stat *dstat,mode_t newperm,struct Promise *pp,struct Attributes attr);
int VerifyFinderType(char *file,struct stat *statbuf,struct Attributes a,struct Promise *pp);
int TransformFile(char *file,struct Attributes attr,struct Promise *pp);
int MoveObstruction(char *from,struct Attributes attr,struct Promise *pp);
void VerifyName(char *path,struct stat *sb,struct Attributes attr,struct Promise *pp);
void VerifyDelete(char *path,struct stat *sb,struct Attributes attr,struct Promise *pp);
void TouchFile(char *path,struct stat *sb,struct Attributes attr,struct Promise *pp); 
int MakeParentDirectory(char *parentandchild,int force);
void LogHashChange(char *file);
void DeleteDirectoryTree(char *path,struct Promise *pp);
struct UidList *MakeUidList(char *uidnames);
struct GidList *MakeGidList(char *gidnames);
void RotateFiles(char *name,int number);
void AddSimpleUidItem(struct UidList **uidlist,int uid,char *uidname);
void AddSimpleGidItem(struct GidList **gidlist,int gid,char *gidname);
void DeleteDirectoryTree(char *path,struct Promise *pp);
void CreateEmptyFile(char *name);
void VerifyFileChanges(char *file,struct stat *sb,struct Promise *pp,struct Attributes attr);

/* files_properties.c */

int ConsiderFile(char *nodename,char *path,struct Attributes attr,struct Promise *pp);
void SetSearchDevice(struct stat *sb,struct Promise *pp);
int DeviceBoundary(struct stat *sb,struct Promise *pp);

/* files_repository.c */

int ArchiveToRepository(char *file,struct Attributes attr,struct Promise *pp);

/* files_select.c */

int SelectLeaf(char *path,struct stat *sb,struct Attributes attr,struct Promise *pp);
int SelectTypeMatch(struct stat *lstatptr,struct Rlist *crit);
int SelectOwnerMatch(struct stat *lstatptr,struct Rlist *crit);
int SelectGroupMatch(struct stat *lstatptr,struct Rlist *crit);
int SelectModeMatch(struct stat *lstatptr,struct Rlist *ls);
int SelectTimeMatch(time_t stattime,time_t fromtime,time_t totime);
int SelectNameRegexMatch(char *filename,char *crit);
int SelectPathRegexMatch(char *filename,char *crit);
int SelectExecRegexMatch(char *filename,char *crit,char *prog);
int SelectIsSymLinkTo(char *filename,struct Rlist *crit);
int SelectExecProgram(char *filename,char *crit);
int SelectSizeMatch(size_t size,size_t min,size_t max);
int SelectBSDMatch(struct stat *lstatptr,struct Rlist *bsdflags,struct Promise *pp);

/* fncall.c */

int IsBuiltinFnCall(void *rval,char rtype);
struct FnCall *NewFnCall(char *name, struct Rlist *args);
struct FnCall *CopyFnCall(struct FnCall *f);
void PrintFunctions(void);
void DeleteFnCall(struct FnCall *fp);
void ShowFnCall(FILE *fout,struct FnCall *fp);
struct Rval EvaluateFunctionCall(struct FnCall *fp,struct Promise *pp);
enum cfdatatype FunctionReturnType(char *name);
enum fncalltype FnCallName(char *name);
void ClearFnCallStatus(void);
void SetFnCallReturnStatus(char *fname,int status,char *message,char *fncall_classes);

/* generic_agent.c */

void GenericInitialize(int argc,char **argv,char *agents);
void PromiseManagement(char *agent);
void InitializeGA(int argc,char **argv);
void CheckOpts(int argc,char **argv);
void CheckWorkingDirectories(void);
void Syntax(char *comp,struct option options[],char *hints[],char *id);
void ManPage(char *component,struct option options[],char *hints[],char *id);
void Version(char *comp);
int CheckPromises(enum cfagenttype ag);
void ReadPromises(enum cfagenttype ag,char *agents);
void Cf3ParseFile(char *filename);
void Cf3ParseFiles(void);
int NewPromiseProposals(void);
void CompilationReport(char *filename);
void HashVariables(void);
void HashControls(void);
void UnHashVariables(void);
void TheAgent(enum cfagenttype ag);
void Cf3OpenLog(void);
void *ExitCleanly(int signum);
struct Constraint *ControlBodyConstraints(enum cfagenttype agent);
void SetFacility(char *retval);
struct Bundle *GetBundle(char *name,char *agent);
struct SubType *GetSubTypeForBundle(char *type,struct Bundle *bp);
void CheckControlPromises(char *scope,char *agent,struct Constraint *controllist);
void CheckVariablePromises(char *scope,struct Promise *varlist);
void CheckCommonClassPromises(struct Promise *classlist);
void CheckBundleParameters(char *scope,struct Rlist *args);
void PromiseBanner(struct Promise *pp);
void BannerBundle(struct Bundle *bp,struct Rlist *args);
void BannerSubBundle(struct Bundle *bp,struct Rlist *args);
void PrependAuditFile(char *file);
void WritePID(char *filename);
void OpenReports(char *agents);
void CloseReports(char *agents);
char *InputLocation(char *filename);
int BadBundleSequence(enum cfagenttype agent);

/* granules.c  */

char *ConvTimeKey (char *str);
char *GenTimeKey (time_t now);

/* graph.c */

void VerifyGraph(struct Topic *map,struct Rlist *list,char *view);
int AlreadyInTribe(int node, int *tribe);
int Degree(double *m,int dim);
int Top(double **adj,double *evc,int topic,int dim);
void PrintNeighbours(double *m,int dim,char **names);
void EigenvectorCentrality(double **A,double *v,int dim);
void MatrixOperation(double **A,double *v,int dim);
void PlotTopicCosmos(int topic,double **adj,char **names,int dim,char *view);
void GetTribe(int *tribe,char **n,int *neigh,int topic,double **adj,int dim);
int AlreadyInTribe(int node, int *tribe);


/* hashes.c */

void InitHashes(struct CfAssoc **table);
void CopyHashes(struct CfAssoc **newhash,struct CfAssoc **oldhash);
void BlankHashes(char *scope);
int GetHash(char *name);
void PrintHashes(FILE *sp,struct CfAssoc **table,int html);
int AddVariableHash(char *scope,char *lval,void *rval,char rtype,enum cfdatatype dtype,char *fname,int no);
void DeleteHashes(struct CfAssoc **hashtable);
void EditHashValue(char *scopeid,char *lval,void *rval);
void DeRefListsInHashtable(char *scope,struct Rlist *list,struct Rlist *reflist);

/* html.c */

void CfHtmlHeader(FILE *fp,char *title,char *css,char *webdriver,char *banner);
void CfHtmlFooter(FILE *fp,char *footer);

/* item-lib.c */

struct Item *EndOfList(struct Item *start);
int IsItemInRegion(char *item,struct Item *begin,struct Item *end);
void AppendItemList(struct Item **liststart,char *itemstring);
void PrependItemList(struct Item **liststart,char *itemstring);
int SelectItemMatching(char *regex,struct Item *begin,struct Item *end,struct Item **match,struct Item **prev,char *fl);
int SelectNextItemMatching(char *regexp,struct Item *begin,struct Item *end,struct Item **match,struct Item **prev);
int SelectLastItemMatching(char *regexp,struct Item *begin,struct Item *end,struct Item **match,struct Item **prev);
int SelectRegion(struct Item *start,struct Item **begin_ptr,struct Item **end_ptr,struct Attributes a,struct Promise *pp);
void InsertAfter(struct Item **filestart,struct Item *ptr,char *string);
int NeighbourItemMatches(struct Item *start,struct Item *location,char *string,enum cfeditorder pos);
int RawSaveItemList(struct Item *liststart, char *file);
struct Item *SplitStringAsItemList(char *string,char sep);
struct Item *SplitString(char *string,char sep);
int DeleteItemGeneral (struct Item **filestart, char *string, enum matchtypes type);
int DeleteItemLiteral (struct Item **filestart, char *string);
int DeleteItemStarting (struct Item **list,char *string);
int DeleteItemNotStarting (struct Item **list,char *string);
int DeleteItemMatching (struct Item **list,char *string);
int DeleteItemNotMatching (struct Item **list,char *string);
int DeleteItemContaining (struct Item **list,char *string);
int DeleteItemNotContaining (struct Item **list,char *string);
int OrderedListsMatch(struct Item *list1,struct Item *list2);
int IsClassedItemIn(struct Item *list,char *item);
int CompareToFile(struct Item *liststart,char *file,struct Attributes a,struct Promise *pp);
struct Item *String2List(char *string);
int ListLen (struct Item *list);
int ByteSizeList (struct Item *list);
int IsItemIn (struct Item *list, char *item);
int IsFuzzyItemIn (struct Item *list, char *item);
int IsMatchItemIn(struct Item *list,char *item);
int GetItemListCounter (struct Item *list, char *item);
struct Item *ConcatLists (struct Item *list1, struct Item *list2);
void CopyList (struct Item **dest,struct Item *source);
int FuzzySetMatch (char *s1, char *s2);
int FuzzyMatchParse (char *item);
int FuzzyHostMatch (char *arg0, char *arg1,char *basename);
int FuzzyHostParse (char *arg1,char *arg2);
void PrependItem  (struct Item **liststart, char *itemstring, char *classes);
void AppendItem  (struct Item **liststart, char *itemstring, char *classes);
void DeleteItemList (struct Item *item);
void DeleteItem (struct Item **liststart, struct Item *item);
void DebugListItemList (struct Item *liststart);
int ItemListsEqual (struct Item *list1, struct Item *list2);
struct Item *SplitStringAsItemList (char *string, char sep);
void IncrementItemListCounter (struct Item *ptr, char *string);
void SetItemListCounter (struct Item *ptr, char *string,int value);
struct Item *SortItemListNames(struct Item *list);
struct Item *SortItemListCounters(struct Item *list);
char *ItemList2CSV(struct Item *list);

/* iteration.c */

struct Rlist *NewIterationContext(char *scopeid,struct Rlist *listvars);
void DeleteIterationContext(struct Rlist *lol);
int IncrementIterationContext(struct Rlist *iterators,int count);
int EndOfIteration(struct Rlist *iterator);

/* instrumentation.c */

struct timespec BeginMeasure(void);
void EndMeasure(char *eventname,struct timespec start);
void EndMeasurePromise(struct timespec start,struct Promise *pp);
void NotePerformance(char *eventname,time_t t,double value);
void NoteClassUsage(struct Item *list);
void LastSaw(char *hostname,enum roles role);
int OpenDB(char *filename,DB **dbp);
int ReadDB(DB *dbp,char *name,void *ptr,int size);
int WriteDB(DB *dbp,char *name,void *ptr,int size);
void DeleteDB(DB *dbp,char *name);
DBT *NewDBKey(char *name);
void DeleteDBKey(DBT *key);
DBT *NewDBValue(void *ptr,int size);
void DeleteDBValue(DBT *value);
double GAverage(double anew,double aold,double p);


/* install.c */

int DeEscapeString(char *from,char *to);
int RelevantBundle(char *agent,char *blocktype);
struct Bundle *AppendBundle(struct Bundle **start,char *name, char *type, struct Rlist *args);
struct Body *AppendBody(struct Body **start,char *name, char *type, struct Rlist *args);
struct SubType *AppendSubType(struct Bundle *bundle,char *typename);
struct SubType *AppendBodyType(struct Body *body,char *typename);
struct Promise *AppendPromise(struct SubType *type,char *promiser, void *promisee,char petype,char *classes,char *bundle,char *bundletype);
void DeleteBundles(struct Bundle *bp);
void DeleteSubTypes(struct SubType *tp);
void DeleteBodies(struct Body *bp);

/* interfaces.c */

void VerifyInterfacePromise(char *vifdev,char *vaddress,char *vnetmask,char *vbroadcast);
int GetPromisedIfStatus(int sk,char *vifdev,char *vaddress,char *vnetmask,char *vbroadcast);
void SetPromisedIfStatus(int sk,char *vifdev,char *vaddress,char *vnetmask,char *vbroadcast);
void GetDefaultBroadcastAddr(char *ipaddr,char *vifdev,char *vnetmask,char *vbroadcast);
void SetPromisedDefaultRoute(void);

/* logging.c */

void BeginAudit(void);
void EndAudit(void);
void ClassAuditLog(struct Promise *pp,struct Attributes attr,char *str,char status);
void AddAllClasses(struct Rlist *list,int persist,enum statepolicy policy);
void ExtractOperationLock(char *op);
void PromiseLog(char *s);
void FatalError(char *s);
void AuditStatusMessage(FILE*fp,char status);

/* manual.c */

void TexinfoManual(char *mandir);

/* matching.c */

int FullTextMatch (char *regptr,char *cmpptr);
int FullTextCaseMatch (char *regexp,char *teststring);
char *ExtractFirstReference(char *regexp,char *teststring);
void CfRegFree(struct CfRegEx rex);
int BlockTextMatch (char *regexp,char *teststring,int *s,int *e);
int BlockTextCaseMatch(char *regexp,char *teststring,int *start,int *end);
int IsRegexItemIn(struct Item *list,char *regex);
int IsPathRegex(char *str);
int IsRegex(char *str);
int MatchRlistItem(struct Rlist *listofregex,char *teststring);
struct CfRegEx CompileRegExp(char *regexp);
struct CfRegEx CaseCompileRegExp(char *regexp);
int RegExMatchSubString(struct CfRegEx rx,char *teststring,int *s,int *e);
int RegExMatchFullString(struct CfRegEx rex,char *teststring);
char *FirstBackReference(struct CfRegEx rex,char *regex,char *teststring);

/* modes.c */

int ParseModeString (char *modestring, mode_t *plusmask, mode_t *minusmask);
int CheckModeState (enum modestate stateA, enum modestate stateB,enum modesort modeA, enum modesort modeB, char ch);
int SetModeMask (char action, int value, int affected, mode_t *p, mode_t *m);

/* net.c */

int SendTransaction (int sd, char *buffer,int len, char status);
int ReceiveTransaction (int sd, char *buffer,int *more);
int RecvSocketStream (int sd, char *buffer, int toget, int nothing);
int SendSocketStream (int sd, char *buffer, int toget, int flags);

/* nfs.c */

int LoadMountInfo(struct Rlist **list);
void AugmentMountInfo(struct Rlist **list,char *host,char *source,char *mounton,char *options);
void DeleteMountInfo(struct Rlist *list);
int VerifyNotInFstab(char *name,struct Attributes a,struct Promise *pp);
int VerifyInFstab(char *name,struct Attributes a,struct Promise *pp);
int VerifyUnmount(char *name,struct Attributes a,struct Promise *pp);
int MatchFSInFstab(char *match);
void DeleteThisItem(struct Item **liststart,struct Item *entry);
void MountAll(void);

/* ontology.c */

void AddTopic(struct Topic **list,char *name,char *type);
void AddCommentedTopic(struct Topic **list,char *name,char *comment,char *type);
void AddTopicAssociation(struct TopicAssociation **list,char *fwd_name,char *bwd_name,struct Rlist *li,int verify);
void AddOccurrence(struct Occurrence **list,char *reference,struct Rlist *represents,enum representations rtype);
int TopicExists(struct Topic *list,char *topic_name,char *topic_type);
char *GetTopicType(struct Topic *list,char *topic_name);
struct Topic *GetCanonizedTopic(struct Topic *list,char *topic_name);
struct Topic *GetTopic(struct Topic *list,char *topic_name);
struct TopicAssociation *AssociationExists(struct TopicAssociation *list,char *fwd,char *bwd,int verify);
struct Occurrence *OccurrenceExists(struct Occurrence *list,char *locator,enum representations repy_type);
int TypedTopicMatch(char *ttopic1,char *ttopic2);
void DeTypeTopic(char *typdetopic,char *topic,char *type);
void DeTypeCanonicalTopic(char *typed_topic,char *topic,char *type);
char *TypedTopic(char *topic,char *type);
char *GetLongTopicName(CfdbConn *cfdb,struct Topic *list,char *topic_name);
char *URLHint(char *s);

/* patches.c */

int IsPrivileged (void);
int IntMin (int a,int b);
char *StrStr (char *s1,char *s2);
int StrnCmp (char *s1,char *s2,size_t n);
int cf_strcmp(char *s1,char *s2);
int cf_strncmp(char *s1,char *s2,size_t n);
char *cf_strdup(char *s);
int cf_strlen(char *s);
char *cf_strncpy(char *s1,char *s2,size_t n);
char *cf_strchr(char *s, int c);
char *cf_strcpy(char *s1,char *s2);
char *MapName(char *s);
int UseUnixStandard(char *s);

#ifndef HAVE_GETNETGRENT
int setnetgrent (const char *netgroup);
int getnetgrent (char **host, char **user, char **domain);
void endnetgrent (void);
#endif
#ifndef HAVE_UNAME
int uname  (struct utsname *name);
#endif
#ifndef HAVE_STRSTR
char *strstr (char *s1,char *s2);
#endif
#ifndef HAVE_STRDUP
char *strdup (char *str);
#endif
#ifndef HAVE_STRRCHR
char *strrchr (char *str,char ch);
#endif
#ifndef HAVE_STRERROR
char *strerror (int err);
#endif
#ifndef HAVE_STRSEP
char *strsep(char **stringp, const char *delim);
#endif
#ifndef HAVE_PUTENV
int putenv  (char *s);
#endif
#ifndef HAVE_SETEUID
int seteuid (uid_t euid);
#endif
#ifndef HAVE_SETEUID
int setegid (gid_t egid);
#endif

/* pipes.c */

FILE *cf_fopen(char *file,char *type);
int cf_fclose(FILE *fp);
FILE *cf_popen(char *command,char *type);
FILE *cf_popensetuid(char *command,char *type,uid_t uid,gid_t gid,char *chdirv,char *chrootv);
FILE *cf_popen_sh(char *command,char *type);
FILE *cf_popen_shsetuid(char *command,char *type,uid_t uid,gid_t gid,char *chdirv,char *chrootv);
int cf_pclose(FILE *pp);
int cf_pclose_def(FILE *pfp,struct Attributes a,struct Promise *pp);
int cf_pwait(pid_t pid);
int CfSetuid(uid_t uid,gid_t gid);
int ArgSplitCommand(char *comm,char arg[CF_MAXSHELLARGS][CF_BUFSIZE]);

/* processes_select.c */

int SelectProcess(char *procentry,char **names,int *start,int *end,struct Attributes a,struct Promise *pp);
int SelectProcRangeMatch(char *name1,char *name2,int min,int max,char **names,char **line);
int SelectProcRegexMatch(char *name1,char *name2,char *regex,char **names,char **line);
int SplitProcLine(char *proc,char **names,int *start,int *end,char **line);
int SelectProcTimeCounterRangeMatch(char *name1,char *name2,time_t min,time_t max,char **names,char **line);
int SelectProcTimeAbsRangeMatch(char *name1,char *name2,time_t min,time_t max,char **names,char **line);

/* promises.c */

char *BodyName(struct Promise *pp);
struct Body *IsBody(struct Body *list,char *key);
struct Bundle *IsBundle(struct Bundle *list,char *key);
struct Promise *DeRefCopyPromise(char *scopeid,struct Promise *pp);
struct Promise *ExpandDeRefPromise(char *scopeid,struct Promise *pp);
struct Promise *CopyPromise(char *scopeid,struct Promise *pp);
void DeletePromise(struct Promise *pp);
void DeletePromises(struct Promise *pp);
void DeleteDeRefPromise(char *scopeid,struct Promise *pp);
void PromiseRef(enum cfreport level,struct Promise *pp);
struct Promise *NewPromise(char *typename,char *promiser);
void HashPromise(char *salt,struct Promise *pp,unsigned char digest[EVP_MAX_MD_SIZE+1],enum cfhashes type);
void DebugPromise(struct Promise *pp);

/* recursion.c */

int DepthSearch(char *name,struct stat *sb,int rlevel,struct Attributes attr,struct Promise *pp);
int PushDirState(char *name,struct stat *sb);
void PopDirState(int goback,char * name,struct stat *sb,struct Recursion r);
int SkipDirLinks(char *path,char *lastnode,struct Recursion r);
int SensibleFile(char *nodename,char *path,struct Attributes,struct Promise *pp);
void CheckLinkSecurity(struct stat *sb,char *name);

/* reporting.c */

void ShowContext(void);
void ShowPromises(struct Bundle *bundles,struct Body *bodies);
void ShowPromise(struct Promise *pp, int indent);
void ShowScopedVariables(void);
void Indent(int i);
void ReportBanner(char *s);
void SyntaxTree(void);
void ShowDataTypes(void);
void ShowControlBodies(void);
void ShowBundleTypes(void);
void ShowPromiseTypesFor(char *s);
void ShowBodyParts(struct BodySyntax *bs);
void ShowRange(char *s,enum cfdatatype type);
void ShowBuiltinFunctions(void);
void ShowBody(struct Body *body,int ident);
void DebugBanner(char *s);
void ReportError(char *s);
void BannerSubType(char *bundlename,char *type,int p);
void BannerSubSubType(char *bundlename,char *type);
void Banner(char *s);

/* rlist.c */

int IsStringIn(struct Rlist *list,char *s);
int IsRegexIn(struct Rlist *list,char *s);
struct Rlist *KeyInRlist(struct Rlist *list,char *key);
int RlistLen(struct Rlist *start);
void PopStack(struct Rlist **liststart, void **item,size_t size);
void PushStack(struct Rlist **liststart,void *item);
int IsInListOfRegex(struct Rlist *list,char *str);

void *CopyRvalItem(void *item, char type);
void DeleteRvalItem(void *rval, char type);
struct Rlist *CopyRlist(struct Rlist *list);
void DeleteRlist(struct Rlist *list);
void DeleteReferenceRlist(struct Rlist *list);
void ShowRlistState(FILE *fp,struct Rlist *list);
void DeleteRlistEntry(struct Rlist **liststart,struct Rlist *entry);
struct Rlist *AppendRlistAlien(struct Rlist **start,void *item);
struct Rlist *OrthogAppendRlist(struct Rlist **start,void *item, char type);
struct Rlist *IdempAppendRScalar(struct Rlist **start,void *item, char type);
struct Rlist *AppendRScalar(struct Rlist **start,void *item, char type);
struct Rlist *IdempAppendRlist(struct Rlist **start,void *item, char type);
struct Rlist *IdempPrependRScalar(struct Rlist **start,void *item, char type);
struct Rlist *PrependRScalar(struct Rlist **start,void *item, char type);
struct Rlist *PrependRlist(struct Rlist **start,void *item, char type);
struct Rlist *AppendRlist(struct Rlist **start,void *item, char type);
struct Rlist *PrependRlist(struct Rlist **start,void *item, char type);
struct Rlist *SplitStringAsRList(char *string,char sep);
struct Rlist *SplitRegexAsRList(char *string,char *regex,int max,int purge);
struct Rlist *AlphaSortRListNames(struct Rlist *list);

void ShowRlist(FILE *fp,struct Rlist *list);
void ShowRval(FILE *fp,void *rval,char type);

    
/* scope.c */

void DebugVariables(char *label);
void SetScope(char *id);
void SetNewScope(char *id);
void NewScope(char *name);
void DeleteScope(char *name);
struct Scope *GetScope(char *scope);
void CopyScope(char *new, char *old);
void DeleteAllScope(void);
void AugmentScope(char *scope,struct Rlist *lvals,struct Rlist *rvals);
void DeleteFromScope(char *scope,struct Rlist *args);
void PushThisScope(void);
void PopThisScope(void);
void ShowScope(char *name);

/* selfdiagnostic.c */

void SelfDiagnostic(void);
void TestVariableScan(void);
void TestExpandPromise(void);
void TestExpandVariables(void);
void TestSearchFilePromiser(void);
void TestRegularExpressions(void);
void TestAgentPromises(void);

/* server_transform.c */

void KeepPromiseBundles(void);
void KeepControlPromises(void);
void KeepServerPromise(struct Promise *pp);
void InstallServerAuthPath(char *path,struct Auth **list,struct Auth **listtop);
void KeepServerRolePromise(struct Promise *pp);
void KeepServerAccessPromise(struct Promise *pp);
struct Auth *GetAuthPath(char *path,struct Auth *list);
void Summarize(void);

/* signals.c */

void HandleSignals(int signum);

/* sockaddr.c */

char *sockaddr_ntop (struct sockaddr *sa);
void *sockaddr_pton (int af,void *src);

/* storage_tools.c */

int GetDiskUsage  (char *file, enum cfsizes type);

/* syntax.c */

void CheckBundle(char *name,char *type);
void CheckBody(char *name,char *type);
struct SubTypeSyntax CheckSubType(char *btype,char *type);
void CheckConstraint(char *type,char *name,char *lval,void *rval,char rvaltype,struct SubTypeSyntax ss);
void CheckSelection(char *type,char *name,char *lval,void *rval,char rvaltype);
void CheckConstraintTypeMatch(char *lval,void *rval,char rvaltype,enum cfdatatype dt,char *range,int level);
int CheckParseString(char *lv,char *s,char *range);
int CheckParseClass(char *lv,char *s,char *range);
void CheckParseInt(char *lv,char *s,char *range);
void CheckParseReal(char *lv,char *s,char *range);
void CheckParseRealRange(char *lval,char *s,char *range);
void CheckParseIntRange(char *lval,char *s,char *range);
void CheckParseOpts(char *lv,char *s,char *range);
void CheckFnCallType(char *lval,char *s,enum cfdatatype dtype,char *range);
enum cfdatatype StringDataType(char *scopeid,char *string);
enum cfdatatype ExpectedDataType(char *lvalname);

/* sysinfo.c */

void GetNameInfo3(void);
void GetInterfaceInfo3(void);
void Get3Environment(void);
void FindV6InterfaceInfo(void);
void FindDomainName(char *hostname);
void OSClasses(void);
int Linux_Fedora_Version(void);
int Linux_Redhat_Version(void);
int Linux_Suse_Version(void);
int Linux_Slackware_Version(char *filename);
int Linux_Debian_Version(void);
int Linux_Old_Mandriva_Version(void);
int Linux_New_Mandriva_Version(void);
int Linux_Mandriva_Version_Real(char *filename, char *relstring, char *vendor);
void * Lsb_Release(const char *command, const char *key);
int Lsb_Version(void);
int VM_Version(void);
int Xen_Domain(void);
void Xen_Cpuid(uint32_t idx, uint32_t *eax, uint32_t *ebx, uint32_t *ecx, uint32_t *edx);
int Xen_Hv_Check(void);
void SetSignals(void);
int IsInterfaceAddress(char *adr);
char *GetHome(uid_t uid);

/* transaction.c */

void SummarizeTransaction(struct Attributes attr,struct Promise *pp,char *logname);
struct CfLock AcquireLock(char *operand,char *host,time_t now,struct Attributes attr,struct Promise *pp);
void YieldCurrentLock(struct CfLock this);
void GetLockName(char *lockname,char *locktype,char *base,struct Rlist *params);
time_t FindLock(char *last);
int WriteLock(char *lock);
int RemoveLock(char *name);
void LogLockCompletion(char *cflog,int pid,char *str,char *operator,char *operand);
time_t FindLockTime(char *name);
pid_t FindLockPid(char *name);
DB *OpenLock(void);
void CloseLock(DB *dbp);

/* timeout.c */

void SetTimeOut(int timeout);
void TimeOut(void);
void DeleteTimeOut(void);
void SetReferenceTime(int setclasses);
void SetStartTime(int setclasses);
void AddTimeClass(char *str);


/* vars.c */

void LoadSystemConstants(void);
void ForceScalar(char *lval,char *rval);
void NewScalar(char *scope,char *lval,char *rval,enum cfdatatype dt);
void IdempNewScalar(char *scope,char *lval,char *rval,enum cfdatatype dt);
void DeleteScalar(char *scope,char *lval);
void NewList(char *scope,char *lval,void *rval,enum cfdatatype dt);
enum cfdatatype GetVariable(char *scope,char *lval,void **returnv,char *rtype);
void DeleteVariable(char *scope,char *id);
int CompareVariable(char *lval,struct CfAssoc *ap);
int CompareVariableValue(void *rval,char rtype,struct CfAssoc *ap);
void DeleteAllVariables(char *scope);
int StringContainsVar(char *s,char *v);
int DefinedVariable(char *name);
int IsCf3VarString(char *str);
int IsCf3Scalar(char *str);
int BooleanControl(char *scope,char *name);
char *ExtractInnerCf3VarString(char *str,char *substr);
char *ExtractOuterCf3VarString(char *str,char *substr);
int UnresolvedVariables(struct CfAssoc *ap,char rtype);
int UnresolvedArgs(struct Rlist *args);

/* verify_databases.c */

void VerifyDatabasePromises(struct Promise *pp);
int CheckDatabaseSanity(struct Attributes a, struct Promise *pp);
void VerifySQLPromise(struct Attributes a,struct Promise *pp);
void VerifyRegistryPromise(struct Attributes a,struct Promise *pp);

/* verify_exec.c */

void VerifyExecPromise(struct Promise *pp);
int ExecSanityChecks(struct Attributes a,struct Promise *pp);
void VerifyExec(struct Attributes a, struct Promise *pp);
void PreviewProtocolLine(char *s,char *comm);

/* verify_files.c */

void FindFilePromiserObjects(struct Promise *pp);
void LocateFilePromiserGroup(char *wildpath,struct Promise *pp,void (*fnptr)(char *path, struct Promise *ptr));
void *FindAndVerifyFilesPromises(struct Promise *pp);
void VerifyFilePromise(char *path,struct Promise *pp);
int FileSanityChecks(char *path,struct Attributes a,struct Promise *pp);

/* verify_interfaces.c */

void VerifyInterface(struct Attributes a,struct Promise *pp);
void VerifyInterfacesPromise(struct Promise *pp);

/* verify_measurements.c */

void VerifyMeasurementPromise(double *this,struct Promise *pp);
int CheckMeasureSanity(struct Attributes a,struct Promise *pp);

/* verify_methods.c */

void VerifyMethodsPromise(struct Promise *pp);
int VerifyMethod(struct Attributes a,struct Promise *pp);

/* verify_packages.c */

void VerifyPromisedPatch(struct Attributes a,struct Promise *pp);
void VerifyPackagesPromise(struct Promise *pp);
void ExecutePackageSchedule(struct CfPackageManager *schedule);
int ExecuteSchedule(struct CfPackageManager *schedule,enum package_actions action);
int ExecutePatch(struct CfPackageManager *schedule,enum package_actions action);
int PackageSanityCheck(struct Attributes a,struct Promise *pp);
int VerifyInstalledPackages(struct CfPackageManager **alllists,struct Attributes a,struct Promise *pp);
void VerifyPromisedPackage(struct Attributes a,struct Promise *pp);
struct CfPackageManager *NewPackageManager(struct CfPackageManager **lists,char *mgr,enum package_actions pa,enum action_policy x);
void DeletePackageManagers(struct CfPackageManager *newlist);
int PrependListPackageItem(struct CfPackageItem **list,char *item,struct Attributes a,struct Promise *pp);
int PrependPackageItem(struct CfPackageItem **list,char *name,char *version,char* arch,struct Attributes a,struct Promise *pp);
void DeletePackageItems(struct CfPackageItem *pi);
int PackageMatch(char *n,char *v,char *a,struct Attributes attr,struct Promise *pp);
int PatchMatch(char *n,char *v,char *a,struct Attributes attr,struct Promise *pp);
int ComparePackages(char *n,char *v,char *a,struct CfPackageItem *pi,enum version_cmp cmp);
void ParsePackageVersion(char *version,struct Rlist *num,struct Rlist *sep);
void SchedulePackageOp(char *name,char *version,char *arch,int installed,int matched,int novers,struct Attributes a,struct Promise *pp);
int ExecPackageCommand(char *command,int verify,struct Attributes a,struct Promise *pp);
int PackageInItemList(struct CfPackageItem *list,char *name,char *version,char *arch);
int PrependPatchItem(struct CfPackageItem **list,char *item,struct CfPackageItem *chklist,struct Attributes a,struct Promise *pp);

/* verify_processes.c */

void VerifyProcessesPromise(struct Promise *pp);
int ProcessSanityChecks(struct Attributes a,struct Promise *pp);
void VerifyProcesses(struct Attributes a, struct Promise *pp);
int LoadProcessTable(struct Item **procdata,char *psopts);
void VerifyProcessOp(struct Item *procdata,struct Attributes a,struct Promise *pp);
int FindPidMatches(struct Item *procdata,struct Item **killlist,struct Attributes a,struct Promise *pp);
int DoAllSignals(struct Item *siglist,struct Attributes a,struct Promise *pp);
int ExtractPid(char *psentry);
void GetProcessColumnNames(char *proc,char **names,int *start,int *end);

/* verify_storage.c */

void *FindAndVerifyStoragePromises(struct Promise *pp);
void FindStoragePromiserObjects(struct Promise *pp);
void VerifyStoragePromise(char *path,struct Promise *pp);
int VerifyMountPromise(char *file,struct Attributes a,struct Promise *pp);
int VerifyFileSystem(char *name,struct Attributes a,struct Promise *pp);
int VerifyFreeSpace(char *file,struct Attributes a,struct Promise *pp);
void VolumeScanArrivals(char *file,struct Attributes a,struct Promise *pp);
int FileSystemMountedCorrectly(struct Rlist *list,char *name,char *options,struct Attributes a,struct Promise *pp);
int IsForeignFileSystem (struct stat *childstat,char *dir);

/* verify_reports.c */

void VerifyReportPromise(struct Promise *pp);
void PrintFile(struct Attributes a,struct Promise *pp);
void ShowState(char *type,struct Attributes a,struct Promise *pp);
void FriendStatus(struct Attributes a,struct Promise *pp);
void VerifyFriendReliability(struct Attributes a,struct Promise *pp);
void VerifyFriendConnections(int hours,struct Attributes a,struct Promise *pp);


