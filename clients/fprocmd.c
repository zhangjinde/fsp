    /*********************************************************************\
    *  Copyright (c) 1991 by Wen-King Su (wen-king@vlsi.cs.caltech.edu)   *
    *                                                                     *
    *  You may copy or modify this file in any manner you wish, provided  *
    *  that this notice is always included, and that you hold the author  *
    *  harmless for any loss or damage resulting from the installation or *
    *  use of this software.                                              *
    \*********************************************************************/

#include "tweak.h"
#include "client_def.h"
#include "c_extern.h"
#include "bsd_extern.h"
#include "my-string.h"
#ifdef STDC_HEADERS
#include <stdlib.h>
#endif
#ifdef HAVE_UNISTD_H
#include <unistd.h>
#endif
#include "printpro.h"

static int get_pro PROTO1(const char *, p)
{
  char *op;
  UBUF *ub;
  
  op = util_abs_path(p);
  
  ub = client_interact(CC_GET_PRO,0L, strlen(op), (unsigned char *)op+1, 0,
		       (unsigned char *)NULLP);
  if(ub->cmd == CC_ERR) {
    fprintf(stderr, "ERR: %s\n",ub->buf);
    return(1);
  }
  printf("%s\n",p);
  print_pro(ub,stdout);
  
  return(0);
}

static int set_pro PROTO2(char *, p, char *, key)
{
  char *op;
  UBUF *ub;
  
  op = util_abs_path(p);
  
  ub = client_interact(CC_SET_PRO,0L, strlen(op), (unsigned char *)op+1,
		       strlen(key)+1, (unsigned char *)key);
  if(ub->cmd == CC_ERR) {
    fprintf(stderr, "ERR: %s\n",ub->buf);
    return(1);
  }
  printf("%s\n",p);
  print_pro(ub,stdout);
  
  return(0);
}

int main PROTO2(int, argc, char **, argv)
{
  char **av, *av2[2], *key;
  
  env_client();
  
  if(argv[1] && (argv[1][0] == '+' || argv[1][0] == '-') && !argv[1][2]) {
    key = *++argv;
    while(*++argv) {
      if(!(av = glob(*argv))) {
	av = av2;
	av2[0] = *argv;
	av2[1] = 0;
      }
      while(*av) set_pro(*av++,key);
    }
  } else {
    if(argv[1]) while(*++argv) {
      if(!(av = glob(*argv))) {
	av = av2;
	av2[0] = *argv;
	av2[1] = 0;
      }
      while(*av) get_pro(*av++);
    } else get_pro(env_dir);
  }
  
  client_done();
  
  exit(0);
}