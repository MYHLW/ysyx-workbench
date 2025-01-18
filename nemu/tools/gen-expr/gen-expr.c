/***************************************************************************************
* Copyright (c) 2014-2024 Zihao Yu, Nanjing University
*
* NEMU is licensed under Mulan PSL v2.
* You can use this software according to the terms and conditions of the Mulan PSL v2.
* You may obtain a copy of Mulan PSL v2 at:
*          http://license.coscl.org.cn/MulanPSL2
*
* THIS SOFTWARE IS PROVIDED ON AN "AS IS" BASIS, WITHOUT WARRANTIES OF ANY KIND,
* EITHER EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO NON-INFRINGEMENT,
* MERCHANTABILITY OR FIT FOR A PARTICULAR PURPOSE.
*
* See the Mulan PSL v2 for more details.
***************************************************************************************/

/***************************************************************************************
* Copyright (c) 2014-2024 Zihao Yu, Nanjing University
*
* NEMU is licensed under Mulan PSL v2.
* You can use this software according to the terms and conditions of the Mulan PSL v2.
* You may obtain a copy of Mulan PSL v2 at:
*          http://license.coscl.org.cn/MulanPSL2
*
* THIS SOFTWARE IS PROVIDED ON AN "AS IS" BASIS, WITHOUT WARRANTIES OF ANY KIND,
* EITHER EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO NON-INFRINGEMENT,
* MERCHANTABILITY OR FIT FOR A PARTICULAR PURPOSE.
*
* See the Mulan PSL v2 for more details.
***************************************************************************************/

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <assert.h>
#include <string.h>

// this should be enough
static char buf[65536] = {};
static char code_buf[65536 + 128] = {}; // a little larger than `buf`
static char *code_format =
"#include <stdio.h>\n"
"int main() { "
"  unsigned result = %s; "
"  printf(\"%%u\", result); "
"  return 0;"
"}";
#define MAX_DEPTH 20
int k = 0;  
int depth=0;
//int last_was_num = 0;  
//int last_was_paren = 0;  
//int last_was_op =1;

static void gen_space(){
	if(rand()%2)
	 buf[k++]=' ';
}
static void gen_num(){
	gen_space();
// if(buf[k-1]==')')	return;
 uint32_t rand_num=rand();
  k+=sprintf(buf+k,"%u",rand_num);
  gen_space();
  //last_was_num=1;
  //last_was_op=0;
//  last_was_paren=0;
}

static void gen_rand_op(){
	//if(last_was_op) return;
	int choose_op = rand()%4;
	if(k==0) {
			gen_num();
	}
	else{	
	switch(choose_op){
    case 0 :buf[k++] = '+';break;
	case 1 :buf[k++] = '-';break;
	case 2 :buf[k++] = '*';break;
	default:buf[k++] = '/';break;
	}
}
	//last_was_op=1;
	//last_was_num=0;
    //last_was_paren=0;
 }

static void gen(char arg){
  //  if(arg==')') last_was_paren=1;
	buf[k++]=arg;
	//last_was_num=0;
//	last_was_op=0;

}
static void gen_rand_expr() {
	if (depth > MAX_DEPTH) {  // 控制递归深度
        gen_num();
        return;
    }
	depth++;
 int choose = rand()%3;
  switch (choose) {
    case 0: gen_num();break;
    case 1:// if((last_was_paren)||(last_was_num)) return; 
			gen('('); gen_rand_expr(); gen(')');
			break;
    case 2: gen_rand_expr(); gen_rand_op(); gen_rand_expr(); break;
  }
  depth--;
}

int main(int argc, char *argv[]) {
  int seed = time(0);
  srand(seed);
  int loop = 1;
  if (argc > 1) {
    sscanf(argv[1], "%d", &loop);
  }
  int i;
  for (i = 0; i < loop; i ++) {
    //last_was_num = 0;
   // last_was_paren = 0;
    //last_was_op =1;
    depth=0;
	k=0;
	memset(buf, 0, sizeof(buf));  
    gen_rand_expr();
    sprintf(code_buf, code_format, buf);
    FILE *fp = fopen("/tmp/.code.c", "w");
    assert(fp != NULL);
    fputs(code_buf, fp);
    fclose(fp);
	int ret = system("gcc /tmp/.code.c -Wall -Werror -o /tmp/.expr");
    if (ret != 0) continue;

    fp = popen("/tmp/.expr", "r");
    assert(fp != NULL);

    uint32_t result;
    ret = fscanf(fp, "%u", &result);
    pclose(fp);

    printf("%u %s\n", result, buf);
  }
  return 0;
}
