/* 
   Copyright (C) Cfengine AS

   This file is part of Cfengine 3 - written and maintained by Cfengine AS.
 
   This program is free software; you can redistribute it and/or modify it
   under the terms of the GNU General Public License as published by the
   Free Software Foundation; version 3.
   
   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.
 
  You should have received a copy of the GNU General Public License  
  along with this program; if not, write to the Free Software
  Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA

  To the extent this program is licensed as part of the Enterprise
  versions of Cfengine, the applicable Commerical Open Source License
  (COSL) may apply to this file if you as a licensee so wish it. See
  included file COSL.txt.

*/

/*****************************************************************************/
/*                                                                           */
/* File: ontology.c                                                          */
/*                                                                           */
/*****************************************************************************/

#include "cf3.defs.h"
#include "cf3.extern.h"

/*****************************************************************************/

void AddTopic(struct Topic **list,char *name,char *type)

{ struct Topic *tp;

if (tp = TopicExists(*list,name,type))
   {
   CfOut(cf_verbose,""," ! Topic %s already defined\n",name);
   }
else
   {
   if ((tp = (struct Topic *)malloc(sizeof(struct Topic))) == NULL)
      {
      CfOut(cf_error,"malloc"," !! Memory failure in AddTopic");
      FatalError("");
      }
   
   if ((tp->topic_name = strdup(name)) == NULL)
      {
      CfOut(cf_error,"malloc"," !! Memory failure in AddTopic");
      FatalError("");
      }
   
   if ((tp->topic_type = strdup(type)) == NULL)
      {
      CfOut(cf_error,"malloc"," !! Memory failure in AddTopic");
      FatalError("");
      }
   
   tp->topic_comment = NULL;
   tp->associations = NULL;
   tp->occurrences = NULL;
   tp->next = *list;
   *list = tp;

   CF_NODES++;
   }
}


/*****************************************************************************/

void AddCommentedTopic(struct Topic **list,char *name,char *comment,char *type)

{ struct Topic *tp;

if (tp = TopicExists(*list,name,type))
   {
   CfOut(cf_verbose,""," -> Topic %s already defined, ok\n",name);

   if (comment && tp->topic_comment == NULL)
      {
      if ((tp->topic_comment = strdup(comment)) == NULL)
         {
         CfOut(cf_error,"malloc","Memory failure in AddTopic");
         FatalError("");
         }
      }
   }
else
   {
   if ((tp = (struct Topic *)malloc(sizeof(struct Topic))) == NULL)
      {
      CfOut(cf_error,"malloc"," !! Memory failure in AddTopic");
      FatalError("");
      }
   
   if ((tp->topic_name = strdup(name)) == NULL)
      {
      CfOut(cf_error,"malloc"," !! Memory failure in AddTopic");
      FatalError("");
      }
   
   if (comment)
      {
      if ((tp->topic_comment = strdup(comment)) == NULL)
         {
         CfOut(cf_error,"malloc","Memory failure in AddTopic");
         FatalError("");
         }
      }
   else
      {
      tp->topic_comment = NULL;
      }
   
   if ((tp->topic_type = strdup(type)) == NULL)
      {
      CfOut(cf_error,"malloc","Memory failure in AddTopic");
      FatalError("");
      }
   
   tp->occurrences = NULL;
   tp->associations = NULL;
   tp->next = *list;
   *list = tp;
   CF_NODES++;
   }
}

/*****************************************************************************/

void AddTopicAssociation(struct TopicAssociation **list,char *fwd_name,char *bwd_name,struct Rlist *associates,int verify)

{ struct TopicAssociation *ta = NULL,*texist;
  char assoc_type[CF_MAXVARSIZE];
  struct Rlist *rp;

strncpy(assoc_type,CanonifyName(fwd_name),CF_MAXVARSIZE-1);

if (associates == NULL || associates->item == NULL)
   {
   CfOut(cf_error," !! A topic must have at least one associate in association %s",fwd_name);
   return;
   }

if ((texist = AssociationExists(*list,fwd_name,bwd_name,verify)) == NULL)
   {
   if ((ta = (struct TopicAssociation *)malloc(sizeof(struct TopicAssociation))) == NULL)
      {
      CfOut(cf_error,"malloc","Memory failure in AddTopicAssociation");
      FatalError("");
      }
   
   if ((ta->fwd_name = strdup(fwd_name)) == NULL)
      {
      CfOut(cf_error,"malloc","Memory failure in AddTopicAssociation");
      FatalError("");
      }

   ta->bwd_name = NULL;
       
   if (bwd_name && ((ta->bwd_name = strdup(bwd_name)) == NULL))
      {
      CfOut(cf_error,"malloc","Memory failure in AddTopicAssociation");
      FatalError("");
      }
   
   if (assoc_type && (ta->assoc_type = strdup(assoc_type)) == NULL)
      {
      CfOut(cf_error,"malloc","Memory failure in AddTopicAssociation");
      FatalError("");
      }

   ta->associates = NULL;
   ta->associate_topic_type = NULL;
   ta->next = *list;
   *list = ta;
   }
else
   {
   ta = texist;
   }

/* Association now exists, so add new members */

for (rp = associates; rp != NULL; rp=rp->next)
   {
   /* Defer checking until we have whole ontlogy - all types */
   CfOut(cf_verbose,""," ---> Adding associate '%s'",rp->item);
   IdempPrependRScalar(&(ta->associates),rp->item,rp->type);
   CF_EDGES++;
   }
}

/*****************************************************************************/

void AddOccurrence(struct Occurrence **list,char *reference,struct Rlist *represents,enum representations rtype)

{ struct Occurrence *op = NULL;
  struct TopRepresentation *tr;
  struct Rlist *rp;

if ((op = OccurrenceExists(*list,reference,rtype)) == NULL)
   {
   if ((op = (struct Occurrence *)malloc(sizeof(struct Occurrence))) == NULL)
      {
      CfOut(cf_error,"malloc","Memory failure in AddOccurrence");
      FatalError("");
      }

   op->represents = NULL;
   op->locator = strdup(reference);
   op->rep_type = rtype;   
   op->next = *list;
   *list = op;
   CF_EDGES++;
   CF_NODES++;
   }

/* Occurrence now exists, so add new subtype promises */

if (represents == NULL)
   {
   CfOut(cf_error,""," !! Topic occurrence \"%s\" claims to represent no aspect of its topic, discarding...",reference);
   return;
   }

for (rp = represents; rp != NULL; rp=rp->next)
   {
   IdempPrependRScalar(&(op->represents),rp->item,rp->type);
   }
}

/*********************************************************************/

char *TypedTopic(char *topic,char *type)

{ static char name[CF_MAXVARSIZE];

Debug("TYPE(%s)/TOPIC(%s)",type,topic);
if (type && strlen(type) > 0)
   {
   snprintf(name,CF_MAXVARSIZE,"%s::%s",type,topic);
   }
else
   {
   snprintf(name,CF_MAXVARSIZE,"%s",topic);
   }

return name;
}

/*********************************************************************/

void DeTypeTopic(char *typed_topic,char *topic,char *type)

{
type[0] = '\0';
topic[0] = '\0';

if (*typed_topic == ':')
   {
   sscanf(typed_topic,"::%255[^\n]",topic);
   }
else if (strstr(typed_topic,"::"))
   {
   sscanf(typed_topic,"%255[^:]::%255[^\n]",type,topic);
   
   if (strlen(topic) == 0)
      {
      sscanf(typed_topic,"::%255[^\n]",topic);
      }
   }
else
   {
   strncpy(topic,typed_topic,CF_MAXVARSIZE-1);
   }
}

/*********************************************************************/

void DeTypeCanonicalTopic(char *typed_topic,char *topic,char *type)

{
type[0] = '\0';
topic[0] = '\0';

if (*typed_topic == '.')
   {
   sscanf(typed_topic,".%255[^\n]",topic);
   }
else if (strstr(typed_topic,"."))
   {
   sscanf(typed_topic,"%255[^.].%255[^\n]",type,topic);
   
   if (strlen(topic) == 0)
      {
      sscanf(typed_topic,".%255[^\n]",topic);
      }
   }
else
   {
   strncpy(topic,typed_topic,CF_MAXVARSIZE-1);
   }
}

/*********************************************************************/

int TypedTopicMatch(char *ttopic1,char *ttopic2)

{ char type1[CF_MAXVARSIZE],topic1[CF_MAXVARSIZE];
  char type2[CF_MAXVARSIZE],topic2[CF_MAXVARSIZE];

if (strcmp(ttopic1,ttopic2) == 0)
   {
   return true;
   }
   
type1[0] = '\0';
topic1[0] = '\0';
type2[0] = '\0';
topic2[0] = '\0';

DeTypeTopic(ttopic1,topic1,type1);
DeTypeTopic(ttopic2,topic2,type2);

if (strlen(type1) > 0 && strlen(type2) > 0)
   {
   if (strcmp(topic1,topic2) == 0 && strcmp(type1,type2) == 0)
      {
      return true;
      }
   }
else
   {
   if (strcmp(topic1,topic2) == 0)
      {
      return true;
      }
   }

return false;
}

/*****************************************************************************/

char *URLHint(char *url)

{ char *sp;

for (sp = url+strlen(url); *sp != '/'; sp--)
   {
   }

return sp;
}

/*****************************************************************************/
/* Level                                                                     */
/*****************************************************************************/

struct Topic *TopicExists(struct Topic *list,char *topic_name,char *topic_type)

{ struct Topic *tp;
  char l[CF_BUFSIZE],r[CF_BUFSIZE];
  
for (tp = list; tp != NULL; tp=tp->next)
   {
   if (strcmp(tp->topic_name,topic_name) == 0)
      {
      if (topic_type && strcmp(tp->topic_type,topic_type) != 0)
         {
         CfOut(cf_inform,""," !! Topic \"%s\" already exists, but it promises type \"%s\" not \"%s\"\n",topic_name,tp->topic_type,topic_type);
         return NULL;         
         }
      else
         {
         return tp;
         }
      }

   strncpy(l,ToLowerStr(tp->topic_name),CF_MAXVARSIZE);
   strncpy(r,ToLowerStr(topic_name),CF_MAXVARSIZE);
   
   if (strcmp(l,r) == 0)
      {
      CfOut(cf_inform,""," ! Topic \"%s\" exists with different capitalization \"%s\" this could be a broken promise\n",topic_name,tp->topic_name);
      }
   }

return NULL;
}

/*****************************************************************************/

struct TopicAssociation *AssociationExists(struct TopicAssociation *list,char *fwd,char *bwd,int verify)

{ struct TopicAssociation *ta;
  int yfwd = false,ybwd = false;
  enum cfreport level;
  char l[CF_BUFSIZE],r[CF_BUFSIZE];

if (verify)
   {
   level = cf_error;
   }
else
   {
   level = cf_verbose;
   }

if (fwd == NULL || (fwd && strlen(fwd) == 0))
   {
   CfOut(cf_error,"","NULL forward association name\n");
   return NULL;
   }

if (bwd == NULL || (bwd && strlen(bwd) == 0))
   {
   CfOut(cf_verbose,"","NULL backward association name\n");
   }

for (ta = list; ta != NULL; ta=ta->next)
   {
   if (fwd && (strcmp(fwd,ta->fwd_name) == 0))
      {
      CfOut(cf_verbose,"","Association %s exists already\n",fwd);
      yfwd = true;
      }
   else if (fwd && ta->fwd_name)
      {
      strncpy(l,ToLowerStr(fwd),CF_MAXVARSIZE);
      strncpy(r,ToLowerStr(ta->fwd_name),CF_MAXVARSIZE);
      
      if (strcmp(l,r) == 0)
         {
         CfOut(cf_error,""," ! Association \"%s\" exists with different capitalization \"%s\"\n",fwd,ta->fwd_name);
         yfwd = true;
         }
      else
         {
         yfwd = false;
         }
      }
   else
      {
      yfwd = false;
      }

   if (bwd && (strcmp(bwd,ta->bwd_name) == 0))
      {
      CfOut(cf_verbose,""," ! Association %s exists already\n",bwd);
      ybwd = true;
      }
   else if (bwd && ta->bwd_name)
      {
      strncpy(l,ToLowerStr(bwd),CF_MAXVARSIZE);
      strncpy(r,ToLowerStr(ta->bwd_name),CF_MAXVARSIZE);
      
      if (strcmp(l,r) == 0)
         {
         CfOut(cf_inform,""," ! Association \"%s\" exists with different capitalization \"%s\"\n",bwd,ta->bwd_name);
         }

      ybwd = true;
      }
   else if (!bwd && ta->bwd_name == NULL)
      {
      ybwd = true;
      }
   else
      {
      ybwd = false;
      }
   
   if (ta->bwd_name && (strcmp(fwd,ta->bwd_name) == 0) && bwd && (strcmp(bwd,ta->fwd_name) == 0))
      {
      CfOut(cf_inform,""," ! Association \"%s\" exists already but in opposite orientation\n",fwd);
      return ta;
      }

   if (yfwd && ybwd)
      {
      return ta;
      }
   }

return NULL;
}

/*****************************************************************************/

struct Occurrence *OccurrenceExists(struct Occurrence *list,char *locator,enum representations rep_type)

{ struct Occurrence *op;
  
for (op = list; op != NULL; op=op->next)
   {
   if (strcmp(locator,op->locator) == 0)
      {
      return op;
      }
   }

return NULL;
}

/*****************************************************************************/

struct Topic *GetTopic(struct Topic *list,char *topic_name)

{ struct Topic *tp;
  char type[CF_MAXVARSIZE],name[CF_MAXVARSIZE],*sp;

strncpy(type,topic_name,CF_MAXVARSIZE-1);
name[0] = '\0';

DeTypeTopic(topic_name,name,type);

for (tp = list; tp != NULL; tp=tp->next)
   {
   if (strlen(type) == 0)
      {
      if (strcmp(topic_name,tp->topic_name) == 0)
         {
         return tp;          
         }
      }
   else
      {
      if ((strcmp(name,tp->topic_name)) == 0 && (strcmp(type,tp->topic_type) == 0))
         {
         return tp;          
         }
      }
   }

return NULL;
}

/*****************************************************************************/

struct Topic *GetCanonizedTopic(struct Topic *list,char *topic_name)

{ struct Topic *tp;
  char type[CF_MAXVARSIZE],name[CF_MAXVARSIZE],*sp;

DeTypeCanonicalTopic(topic_name,name,type);

for (tp = list; tp != NULL; tp=tp->next)
   {
   if (strlen(type) == 0)
      {
      if (strcmp(name,CanonifyName(tp->topic_name)) == 0)
         {
         return tp;          
         }
      }
   else
      {
      if ((strcmp(name,CanonifyName(tp->topic_name))) == 0 && (strcmp(type,CanonifyName(tp->topic_type)) == 0))
         {
         return tp;          
         }
      }
   }

return NULL;
}

/*****************************************************************************/

char *GetTopicType(struct Topic *list,char *topic_name)

{ struct Topic *tp;
  static char type1[CF_MAXVARSIZE],topic1[CF_MAXVARSIZE];

type1[0] = '\0';
DeTypeTopic(topic_name,topic1,type1);

if (strlen(type1) > 0)
   {
   return type1;
   }

for (tp = list; tp != NULL; tp=tp->next)
   {
   if (strcmp(topic1,tp->topic_name) == 0)
      {
      return tp->topic_type;
      }
   }

return NULL;
}

