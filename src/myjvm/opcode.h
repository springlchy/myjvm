#ifndef OPCODE_H
#define OPCODE_H

#define OPCODE_MAX 203
#define RETURNV return

#define TO_BYTE(pc) ((*(pc) & 0x80) > 0 ? ((*(pc) & 0x7f)-128) : (*(pc)))
#define TO_CHAR(pc) *(pc)
#define TO_SHORT(pc) *(short*)(pc)
#define TO_INT(pc) *(int*)(pc)


#define PRINTLN printf("\n")
#define PRINTD(x) printf("%d",x)
#define PRINTSD(x) fprintf(stderr, "#%d", x)

#define SWAP(p,index0,index1) *(p+index1)^=(*(p+index0));\
    *(p+index0)^=(*(p+index1));\
    *(p+index1)^=(*(p+index0));
#define BE2LE2(p) SWAP(p,0,1)
#define BE2LE4(p) SWAP(p,0,3);\
    SWAP(p,1,2)
#define BE2LE8(p) SWAP(p,0,7);\
    SWAP(p,1,6);\
    SWAP(p,2,5);\
    SWAP(p,3,4)

#define INC_PC(pc)  (pc)+=1
#define INC2_PC(pc) (pc)+=2
#define INC3_PC(pc) (pc)+=3
#define INC4_PC(pc) (pc)+=4
#define INC8_PC(pc) (pc)+=8

#endif // OPCODE_H
