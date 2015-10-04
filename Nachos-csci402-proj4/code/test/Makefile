# use normal make for this Makefile
#
# Makefile for building user programs to run on top of Nachos
#
# Several things to be aware of:
#
#    Nachos assumes that the location of the program startup routine (the
# 	location the kernel jumps to when the program initially starts up)
#       is at location 0.  This means: start.o must be the first .o passed 
# 	to ld, in order for the routine "Start" to be loaded at location 0
#

# If you are running on SunOS 5.x machines, uncomment the next line
GCCDIR = /auto/home-scf-22/csci402/testgnu/decstation-ultrix/bin/
LDFLAGS = -T newscript -N
ASFLAGS = -mips1
CPPFLAGS = $(INCDIR)

# if you aren't cross-compiling:
# GCCDIR =
# LDFLAGS = -N -T 0
# ASFLAGS =
# CPPFLAGS = -P $(INCDIR)


CC = $(GCCDIR)gcc
AS = $(GCCDIR)as
LD = $(GCCDIR)ld
CPP = $(GCCDIR)cpp

INCDIR =-I../userprog -I../threads
CFLAGS = -G 0 -c $(INCDIR)

all: ticketClerk customerHead simulatorExecTC simulatorExecCustHead concessionClerk simulatorExecCC customer ticketTaker simulatorExecTT Manager simulatorExecManagerTech Technician tc0_1 tc0_2 tc0_3 tc0_4 tc0_5 tcase1 tcase2 tcase3_1 tcase3_2 tcase4_1 tcase4_2 tcase5_1 tcase5_2 tcase6 tcase7_1 tcase7_2 tcase7_3 tcase8_1 tcase8_2 MultiCreates MultiCreatesFile

start.o: start.s ../userprog/syscall.h
	$(CPP) $(CPPFLAGS) start.s > strt.s
	$(AS) $(ASFLAGS) -o start.o strt.s
	rm strt.s

halt.o: halt.c
	$(CC) $(CFLAGS) -c halt.c
halt: halt.o start.o
	$(LD) $(LDFLAGS) start.o halt.o -o halt.coff
	../bin/coff2noff halt.coff halt

halt2.o: halt2.c
	$(CC) $(CFLAGS) -c halt2.c
halt2: halt2.o start.o
	$(LD) $(LDFLAGS) start.o halt2.o -o halt2.coff
	../bin/coff2noff halt2.coff halt2

sort.o: sort.c
	$(CC) $(CFLAGS) -c sort.c
sort: sort.o start.o
	$(LD) $(LDFLAGS) start.o sort.o -o sort.coff
	../bin/coff2noff sort.coff sort

matmult.o: matmult.c
	$(CC) $(CFLAGS) -c matmult.c
matmult: matmult.o start.o
	$(LD) $(LDFLAGS) start.o matmult.o -o matmult.coff
	../bin/coff2noff matmult.coff matmult

testfiles.o: testfiles.c
	$(CC) $(CFLAGS) -c testfiles.c
testfiles: testfiles.o start.o
	$(LD) $(LDFLAGS) start.o testfiles.o -o testfiles.coff
	../bin/coff2noff testfiles.coff testfiles

xyz.o: xyz.c
	$(CC) $(CFLAGS) -c xyz.c
xyz: xyz.o start.o
	$(LD) $(LDFLAGS) start.o xyz.o -o xyz.coff
	../bin/coff2noff xyz.coff xyz
	
TestCase1.o: TestCase1.c
	$(CC) $(CFLAGS) -c TestCase1.c
TestCase1: TestCase1.o start.o
	$(LD) $(LDFLAGS) start.o TestCase1.o -o TestCase1.coff
	../bin/coff2noff TestCase1.coff TestCase1
	
TestCase2.o: TestCase2.c
	$(CC) $(CFLAGS) -c TestCase2.c
TestCase2: TestCase2.o start.o
	$(LD) $(LDFLAGS) start.o TestCase2.o -o TestCase2.coff
	../bin/coff2noff TestCase2.coff TestCase2

TestCase3.o: TestCase3.c
	$(CC) $(CFLAGS) -c TestCase3.c
TestCase3: TestCase3.o start.o
	$(LD) $(LDFLAGS) start.o TestCase3.o -o TestCase3.coff
	../bin/coff2noff TestCase3.coff TestCase3
	
TestCase4.o: TestCase4.c
	$(CC) $(CFLAGS) -c TestCase4.c
TestCase4: TestCase4.o start.o
	$(LD) $(LDFLAGS) start.o TestCase4.o -o TestCase4.coff
	../bin/coff2noff TestCase4.coff TestCase4	
	
TestCase5.o: TestCase5.c
	$(CC) $(CFLAGS) -c TestCase5.c
TestCase5: TestCase5.o start.o
	$(LD) $(LDFLAGS) start.o TestCase5.o -o TestCase5.coff
	../bin/coff2noff TestCase5.coff TestCase5

multiTest.o: multiTest.c
	$(CC) $(CFLAGS) -c multiTest.c
multiTest: multiTest.o start.o
	$(LD) $(LDFLAGS) start.o multiTest.o -o multiTest.coff
	../bin/coff2noff multiTest.coff multiTest


hammer1.o: hammer1.c
	$(CC) $(CFLAGS) -c hammer1.c
hammer1: hammer1.o start.o
	$(LD) $(LDFLAGS) start.o hammer1.o -o hammer1.coff
	../bin/coff2noff hammer1.coff hammer1


TestCase6.o: TestCase6.c
	$(CC) $(CFLAGS) -c TestCase6.c
TestCase6: TestCase6.o start.o
	$(LD) $(LDFLAGS) start.o TestCase6.o -o TestCase6.coff
	../bin/coff2noff TestCase6.coff TestCase6

TestCase15.o: TestCase15.c
	$(CC) $(CFLAGS) -c TestCase15.c
TestCase15: TestCase15.o start.o
	$(LD) $(LDFLAGS) start.o TestCase15.o -o TestCase15.coff
	../bin/coff2noff TestCase15.coff TestCase15

OutOfRange.o: OutOfRange.c
	$(CC) $(CFLAGS) -c OutOfRange.c
OutOfRange: OutOfRange.o start.o
	$(LD) $(LDFLAGS) start.o OutOfRange.o -o OutOfRange.coff
	../bin/coff2noff OutOfRange.coff OutOfRange

NullLockOrCV.o: NullLockOrCV.c
	$(CC) $(CFLAGS) -c NullLockOrCV.c
NullLockOrCV: NullLockOrCV.o start.o
	$(LD) $(LDFLAGS) start.o NullLockOrCV.o -o NullLockOrCV.coff
	../bin/coff2noff NullLockOrCV.coff NullLockOrCV

CreaterProc.o: CreaterProc.c
	$(CC) $(CFLAGS) -c CreaterProc.c
CreaterProc: CreaterProc.o start.o
	$(LD) $(LDFLAGS) start.o CreaterProc.o -o CreaterProc.coff
	../bin/coff2noff CreaterProc.coff CreaterProc
	
IllegalUser.o: IllegalUser.c
	$(CC) $(CFLAGS) -c IllegalUser.c
IllegalUser: IllegalUser.o start.o
	$(LD) $(LDFLAGS) start.o IllegalUser.o -o IllegalUser.coff
	../bin/coff2noff IllegalUser.coff IllegalUser	

testCase_18a.o: testCase_18a.c
	$(CC) $(CFLAGS) -c testCase_18a.c
testCase_18a: testCase_18a.o start.o
	$(LD) $(LDFLAGS) start.o testCase_18a.o -o testCase_18a.coff
	../bin/coff2noff testCase_18a.coff testCase_18a	
	
testCase_18b.o: testCase_18b.c
	$(CC) $(CFLAGS) -c testCase_18b.c
testCase_18b: testCase_18b.o start.o
	$(LD) $(LDFLAGS) start.o testCase_18b.o -o testCase_18b.coff
	../bin/coff2noff testCase_18b.coff testCase_18b
	
TestCase18.o: TestCase18.c
	$(CC) $(CFLAGS) -c TestCase18.c
TestCase18: TestCase18.o start.o
	$(LD) $(LDFLAGS) start.o TestCase18.o -o TestCase18.coff
	../bin/coff2noff TestCase18.coff TestCase18	

tc1_1.o: tc1_1.c
	$(CC) $(CFLAGS) -c tc1_1.c
tc1_1: tc1_1.o start.o
	$(LD) $(LDFLAGS) start.o tc1_1.o -o tc1_1.coff
	../bin/coff2noff tc1_1.coff tc1_1

tc1_2.o: tc1_2.c
	$(CC) $(CFLAGS) -c tc1_2.c
tc1_2: tc1_2.o start.o
	$(LD) $(LDFLAGS) start.o tc1_2.o -o tc1_2.coff
	../bin/coff2noff tc1_2.coff tc1_2

tc2_1.o: tc2_1.c
	$(CC) $(CFLAGS) -c tc2_1.c
tc2_1: tc2_1.o start.o
	$(LD) $(LDFLAGS) start.o tc2_1.o -o tc2_1.coff
	../bin/coff2noff tc2_1.coff tc2_1

tc2_2.o: tc2_2.c
	$(CC) $(CFLAGS) -c tc2_2.c
tc2_2: tc2_2.o start.o
	$(LD) $(LDFLAGS) start.o tc2_2.o -o tc2_2.coff
	../bin/coff2noff tc2_2.coff tc2_2

tc3.o: tc3.c
	$(CC) $(CFLAGS) -c tc3.c
tc3: tc3.o start.o
	$(LD) $(LDFLAGS) start.o tc3.o -o tc3.coff
	../bin/coff2noff tc3.coff tc3

tc4_1.o: tc4_1.c
	$(CC) $(CFLAGS) -c tc4_1.c
tc4_1: tc4_1.o start.o
	$(LD) $(LDFLAGS) start.o tc4_1.o -o tc4_1.coff
	../bin/coff2noff tc4_1.coff tc4_1


tc4_2.o: tc4_2.c
	$(CC) $(CFLAGS) -c tc4_2.c
tc4_2: tc4_2.o start.o
	$(LD) $(LDFLAGS) start.o tc4_2.o -o tc4_2.coff
	../bin/coff2noff tc4_2.coff tc4_2

tc5_1.o: tc5_1.c
	$(CC) $(CFLAGS) -c tc5_1.c
tc5_1: tc5_1.o start.o
	$(LD) $(LDFLAGS) start.o tc5_1.o -o tc5_1.coff
	../bin/coff2noff tc5_1.coff tc5_1

tc5_2.o: tc5_2.c
	$(CC) $(CFLAGS) -c tc5_2.c
tc5_2: tc5_2.o start.o
	$(LD) $(LDFLAGS) start.o tc5_2.o -o tc5_2.coff
	../bin/coff2noff tc5_2.coff tc5_2

tc6_1.o: tc6_1.c
	$(CC) $(CFLAGS) -c tc6_1.c
tc6_1: tc6_1.o start.o
	$(LD) $(LDFLAGS) start.o tc6_1.o -o tc6_1.coff
	../bin/coff2noff tc6_1.coff tc6_1

tc6_2.o: tc6_2.c
	$(CC) $(CFLAGS) -c tc6_2.c
tc6_2: tc6_2.o start.o
	$(LD) $(LDFLAGS) start.o tc6_2.o -o tc6_2.coff
	../bin/coff2noff tc6_2.coff tc6_2

tc6_3.o: tc6_3.c
	$(CC) $(CFLAGS) -c tc6_3.c
tc6_3: tc6_3.o start.o
	$(LD) $(LDFLAGS) start.o tc6_3.o -o tc6_3.coff
	../bin/coff2noff tc6_3.coff tc6_3

tc7_1.o: tc7_1.c
	$(CC) $(CFLAGS) -c tc7_1.c
tc7_1: tc7_1.o start.o
	$(LD) $(LDFLAGS) start.o tc7_1.o -o tc7_1.coff
	../bin/coff2noff tc7_1.coff tc7_1

tc7_2.o: tc7_2.c
	$(CC) $(CFLAGS) -c tc7_2.c
tc7_2: tc7_2.o start.o
	$(LD) $(LDFLAGS) start.o tc7_2.o -o tc7_2.coff
	../bin/coff2noff tc7_2.coff tc7_2

tc8_1.o: tc8_1.c
	$(CC) $(CFLAGS) -c tc8_1.c
tc8_1: tc8_1.o start.o
	$(LD) $(LDFLAGS) start.o tc8_1.o -o tc8_1.coff
	../bin/coff2noff tc8_1.coff tc8_1

tc8_2.o: tc8_2.c
	$(CC) $(CFLAGS) -c tc8_2.c
tc8_2: tc8_2.o start.o
	$(LD) $(LDFLAGS) start.o tc8_2.o -o tc8_2.coff
	../bin/coff2noff tc8_2.coff tc8_2

tc9.o: tc9.c
	$(CC) $(CFLAGS) -c tc9.c
tc9: tc9.o start.o
	$(LD) $(LDFLAGS) start.o tc9.o -o tc9.coff
	../bin/coff2noff tc9.coff tc9

tc10_1.o: tc10_1.c
	$(CC) $(CFLAGS) -c tc10_1.c
tc10_1: tc10_1.o start.o
	$(LD) $(LDFLAGS) start.o tc10_1.o -o tc10_1.coff
	../bin/coff2noff tc10_1.coff tc10_1

tc10_2.o: tc10_2.c
	$(CC) $(CFLAGS) -c tc10_2.c
tc10_2: tc10_2.o start.o
	$(LD) $(LDFLAGS) start.o tc10_2.o -o tc10_2.coff
	../bin/coff2noff tc10_2.coff tc10_2

tc11_1.o: tc11_1.c
	$(CC) $(CFLAGS) -c tc11_1.c
tc11_1: tc11_1.o start.o
	$(LD) $(LDFLAGS) start.o tc11_1.o -o tc11_1.coff
	../bin/coff2noff tc11_1.coff tc11_1

tc11_2.o: tc11_2.c
	$(CC) $(CFLAGS) -c tc11_2.c
tc11_2: tc11_2.o start.o
	$(LD) $(LDFLAGS) start.o tc11_2.o -o tc11_2.coff
	../bin/coff2noff tc11_2.coff tc11_2

ticketClerk.o: ticketClerk.c
	$(CC) $(CFLAGS) -c ticketClerk.c
ticketClerk: ticketClerk.o start.o
	$(LD) $(LDFLAGS) start.o ticketClerk.o -o ticketClerk.coff
	../bin/coff2noff ticketClerk.coff ticketClerk

customerHead.o: customerHead.c
	$(CC) $(CFLAGS) -c customerHead.c
customerHead: customerHead.o start.o
	$(LD) $(LDFLAGS) start.o customerHead.o -o customerHead.coff
	../bin/coff2noff customerHead.coff customerHead

simulatorExecTC.o: simulatorExecTC.c
	$(CC) $(CFLAGS) -c simulatorExecTC.c
simulatorExecTC: simulatorExecTC.o start.o
	$(LD) $(LDFLAGS) start.o simulatorExecTC.o -o simulatorExecTC.coff
	../bin/coff2noff simulatorExecTC.coff simulatorExecTC

simulatorExecCustHead.o: simulatorExecCustHead.c
	$(CC) $(CFLAGS) -c simulatorExecCustHead.c
simulatorExecCustHead: simulatorExecCustHead.o start.o
	$(LD) $(LDFLAGS) start.o simulatorExecCustHead.o -o simulatorExecCustHead.coff
	../bin/coff2noff simulatorExecCustHead.coff simulatorExecCustHead

simulatorExecCC.o: simulatorExecCC.c
	$(CC) $(CFLAGS) -c simulatorExecCC.c
simulatorExecCC: simulatorExecCC.o start.o
	$(LD) $(LDFLAGS) start.o simulatorExecCC.o -o simulatorExecCC.coff
	../bin/coff2noff simulatorExecCC.coff simulatorExecCC

concessionClerk.o: concessionClerk.c
	$(CC) $(CFLAGS) -c concessionClerk.c
concessionClerk: concessionClerk.o start.o
	$(LD) $(LDFLAGS) start.o concessionClerk.o -o concessionClerk.coff
	../bin/coff2noff concessionClerk.coff concessionClerk

customer.o: customer.c
	$(CC) $(CFLAGS) -c customer.c
customer: customer.o start.o
	$(LD) $(LDFLAGS) start.o customer.o -o customer.coff
	../bin/coff2noff customer.coff customer

ticketTaker.o: ticketTaker.c
	$(CC) $(CFLAGS) -c ticketTaker.c
ticketTaker: ticketTaker.o start.o
	$(LD) $(LDFLAGS) start.o ticketTaker.o -o ticketTaker.coff
	../bin/coff2noff ticketTaker.coff ticketTaker

simulatorExecTT.o: simulatorExecTT.c
	$(CC) $(CFLAGS) -c simulatorExecTT.c
simulatorExecTT: simulatorExecTT.o start.o
	$(LD) $(LDFLAGS) start.o simulatorExecTT.o -o simulatorExecTT.coff
	../bin/coff2noff simulatorExecTT.coff simulatorExecTT

Manager.o: Manager.c
	$(CC) $(CFLAGS) -c Manager.c
Manager: Manager.o start.o
	$(LD) $(LDFLAGS) start.o Manager.o -o Manager.coff
	../bin/coff2noff Manager.coff Manager

simulatorExecManagerTech.o: simulatorExecManagerTech.c
	$(CC) $(CFLAGS) -c simulatorExecManagerTech.c
simulatorExecManagerTech: simulatorExecManagerTech.o start.o
	$(LD) $(LDFLAGS) start.o simulatorExecManagerTech.o -o simulatorExecManagerTech.coff
	../bin/coff2noff simulatorExecManagerTech.coff simulatorExecManagerTech



Technician.o: Technician.c
	$(CC) $(CFLAGS) -c Technician.c
Technician: Technician.o start.o
	$(LD) $(LDFLAGS) start.o Technician.o -o Technician.coff
	../bin/coff2noff Technician.coff Technician



tc0_1.o: tc0_1.c
	$(CC) $(CFLAGS) -c tc0_1.c
tc0_1: tc0_1.o start.o
	$(LD) $(LDFLAGS) start.o tc0_1.o -o tc0_1.coff
	../bin/coff2noff tc0_1.coff tc0_1

tc0_2.o: tc0_2.c
	$(CC) $(CFLAGS) -c tc0_2.c
tc0_2: tc0_2.o start.o
	$(LD) $(LDFLAGS) start.o tc0_2.o -o tc0_2.coff
	../bin/coff2noff tc0_2.coff tc0_2

tc0_3.o: tc0_3.c
	$(CC) $(CFLAGS) -c tc0_3.c
tc0_3: tc0_3.o start.o
	$(LD) $(LDFLAGS) start.o tc0_3.o -o tc0_3.coff
	../bin/coff2noff tc0_3.coff tc0_3

tc0_4.o: tc0_4.c
	$(CC) $(CFLAGS) -c tc0_4.c
tc0_4: tc0_4.o start.o
	$(LD) $(LDFLAGS) start.o tc0_4.o -o tc0_4.coff
	../bin/coff2noff tc0_4.coff tc0_4

tc0_5.o: tc0_5.c
	$(CC) $(CFLAGS) -c tc0_5.c
tc0_5: tc0_5.o start.o
	$(LD) $(LDFLAGS) start.o tc0_5.o -o tc0_5.coff
	../bin/coff2noff tc0_5.coff tc0_5


tcase1.o: tcase1.c
	$(CC) $(CFLAGS) -c tcase1.c
tcase1: tcase1.o start.o
	$(LD) $(LDFLAGS) start.o tcase1.o -o tcase1.coff
	../bin/coff2noff tcase1.coff tcase1


tcase2.o: tcase2.c
	$(CC) $(CFLAGS) -c tcase2.c
tcase2: tcase2.o start.o
	$(LD) $(LDFLAGS) start.o tcase2.o -o tcase2.coff
	../bin/coff2noff tcase2.coff tcase2


tcase3_1.o: tcase3_1.c
	$(CC) $(CFLAGS) -c tcase3_1.c
tcase3_1: tcase3_1.o start.o
	$(LD) $(LDFLAGS) start.o tcase3_1.o -o tcase3_1.coff
	../bin/coff2noff tcase3_1.coff tcase3_1


tcase3_2.o: tcase3_2.c
	$(CC) $(CFLAGS) -c tcase3_2.c
tcase3_2: tcase3_2.o start.o
	$(LD) $(LDFLAGS) start.o tcase3_2.o -o tcase3_2.coff
	../bin/coff2noff tcase3_2.coff tcase3_2


tcase4_1.o: tcase4_1.c
	$(CC) $(CFLAGS) -c tcase4_1.c
tcase4_1: tcase4_1.o start.o
	$(LD) $(LDFLAGS) start.o tcase4_1.o -o tcase4_1.coff
	../bin/coff2noff tcase4_1.coff tcase4_1


tcase4_2.o: tcase4_2.c
	$(CC) $(CFLAGS) -c tcase4_2.c
tcase4_2: tcase4_2.o start.o
	$(LD) $(LDFLAGS) start.o tcase4_2.o -o tcase4_2.coff
	../bin/coff2noff tcase4_2.coff tcase4_2


tcase5_1.o: tcase5_1.c
	$(CC) $(CFLAGS) -c tcase5_1.c
tcase5_1: tcase5_1.o start.o
	$(LD) $(LDFLAGS) start.o tcase5_1.o -o tcase5_1.coff
	../bin/coff2noff tcase5_1.coff tcase5_1


tcase5_2.o: tcase5_2.c
	$(CC) $(CFLAGS) -c tcase5_2.c
tcase5_2: tcase5_2.o start.o
	$(LD) $(LDFLAGS) start.o tcase5_2.o -o tcase5_2.coff
	../bin/coff2noff tcase5_2.coff tcase5_2


tcase6.o: tcase6.c
	$(CC) $(CFLAGS) -c tcase6.c
tcase6: tcase6.o start.o
	$(LD) $(LDFLAGS) start.o tcase6.o -o tcase6.coff
	../bin/coff2noff tcase6.coff tcase6


tcase7_1.o: tcase7_1.c
	$(CC) $(CFLAGS) -c tcase7_1.c
tcase7_1: tcase7_1.o start.o
	$(LD) $(LDFLAGS) start.o tcase7_1.o -o tcase7_1.coff
	../bin/coff2noff tcase7_1.coff tcase7_1


tcase7_2.o: tcase7_2.c
	$(CC) $(CFLAGS) -c tcase7_2.c
tcase7_2: tcase7_2.o start.o
	$(LD) $(LDFLAGS) start.o tcase7_2.o -o tcase7_2.coff
	../bin/coff2noff tcase7_2.coff tcase7_2

tcase7-3.o: tcase7-3.c
	$(CC) $(CFLAGS) -c tcase7-3.c
tcase7-3: tcase7-3.o start.o
	$(LD) $(LDFLAGS) start.o tcase7-3.o -o tcase7-3.coff
	../bin/coff2noff tcase7-3.coff tcase7-3

tcase8_1.o: tcase8_1.c
	$(CC) $(CFLAGS) -c tcase8_1.c
tcase8_1: tcase8_1.o start.o
	$(LD) $(LDFLAGS) start.o tcase8_1.o -o tcase8_1.coff
	../bin/coff2noff tcase8_1.coff tcase8_1


tcase8_2.o: tcase8_2.c
	$(CC) $(CFLAGS) -c tcase8_2.c
tcase8_2: tcase8_2.o start.o
	$(LD) $(LDFLAGS) start.o tcase8_2.o -o tcase8_2.coff
	../bin/coff2noff tcase8_2.coff tcase8_2


MultiCreates.o: MultiCreates.c
	$(CC) $(CFLAGS) -c MultiCreates.c
MultiCreates: MultiCreates.o start.o
	$(LD) $(LDFLAGS) start.o MultiCreates.o -o MultiCreates.coff
	../bin/coff2noff MultiCreates.coff MultiCreates


MultiCreatesFile.o: MultiCreatesFile.c
	$(CC) $(CFLAGS) -c MultiCreatesFile.c
MultiCreatesFile: MultiCreatesFile.o start.o
	$(LD) $(LDFLAGS) start.o MultiCreatesFile.o -o MultiCreatesFile.coff
	../bin/coff2noff MultiCreatesFile.coff MultiCreatesFile

clean:
	rm -f *.o *.coff
