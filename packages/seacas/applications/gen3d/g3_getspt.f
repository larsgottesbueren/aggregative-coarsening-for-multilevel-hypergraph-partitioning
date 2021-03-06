C Copyright(C) 2011 Sandia Corporation.  Under the terms of Contract
C DE-AC04-94AL85000 with Sandia Corporation, the U.S. Government retains
C certain rights in this software
C 
C Redistribution and use in source and binary forms, with or without
C modification, are permitted provided that the following conditions are
C met:
C 
C * Redistributions of source code must retain the above copyright
C    notice, this list of conditions and the following disclaimer.
C           
C * Redistributions in binary form must reproduce the above
C   copyright notice, this list of conditions and the following
C   disclaimer in the documentation and/or other materials provided
C   with the distribution.
C                         
C * Neither the name of Sandia Corporation nor the names of its
C   contributors may be used to endorse or promote products derived
C   from this software without specific prior written permission.
C                                                 
C THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
C "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
C LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
C A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
C OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
C SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
C LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
C DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
C THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
C (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
C OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
C 

      SUBROUTINE GETSPT(A)
      DIMENSION A(*)
      INCLUDE 'g3_splxyz.blk'
      
      PARAMETER (BINGO = 1.0E38)
      PARAMETER (MAXFLD = 10)
      PARAMETER (NDEFS = 64)
      CHARACTER*8 WORD, VERB
      INTEGER     INTYP(MAXFLD)
      CHARACTER*8 CFIELD(MAXFLD)
      INTEGER     IFIELD(MAXFLD)
      REAL        RFIELD(MAXFLD)
      
      LOGICAL MATSTR, HELP, ISHELP
      
      CHARACTER*8 CMDTBL(6)
      SAVE CMDTBL
C     --CMDTBL - the valid commands table
      
C     --Command table follows.  Remember to change the dimensioned size when
C     --changing the table.
      DATA CMDTBL /
     1     'SLOPE   ', 'END     ', 'EXIT    ', 'LIST    ', 'HELP    ',
     3     '        ' /
      
      CALL SHOCMD ('COMMANDS', CMDTBL)
      
C     ... Initialize default values
      
      IPT = 0
      SLBOT(1) = BINGO
      SLTOP(1) = BINGO
      SLBOT(2) = BINGO
      SLTOP(2) = BINGO
      ISPL = 1
      
C     ... Allocate arrays, guess on amount and increase if more points entered.
      
      CALL MDRSRV ('ZSPL',  KZSPL,  NDEFS)
      CALL MDRSRV ('XSPL',  KXSPL,  NDEFS)
      CALL MDRSRV ('YSPL',  KYSPL,  NDEFS)
      CALL MDSTAT (NERR, MEM)
      IF (NERR .GT. 0) THEN
         CALL MEMERR
         STOP 'Memory Allocation in GETSPL'
      END IF
      
      NTOT = NDEFS
      
   10 CONTINUE
      
C     --Read command line
      
      WRITE (*, *)
      CALL FREFLD (0, 0, '   Spline Option > ', MAXFLD,
     &     IOSTAT, NUMFLD, INTYP, CFIELD, IFIELD, RFIELD)
      IF (IOSTAT .LT. 0) GOTO 20
      IF (NUMFLD .EQ. 0) GOTO 10
      INTYP(MIN(MAXFLD,NUMFLD)+1) = -999
      
      IFLD = 1
      CALL FFCHAR (IFLD, INTYP, CFIELD, ' ', WORD)
      CALL ABRSTR (VERB, WORD, CMDTBL)
      IF (VERB .EQ. ' ') VERB = WORD
      
      IF (VERB .EQ. 'EXIT' .OR. VERB .EQ. 'END') GO TO 20
      
      IF (VERB .EQ. 'HELP') THEN
         ISHELP = HELP ('GEN3D', 'COMMANDS', CFIELD(IFLD))
         IF (.NOT. ISHELP) CALL SHOCMD ('COMMANDS', CMDTBL)
         VERB = ' '
      END IF

      IF (INTYP(1) .EQ. 0) THEN
         IF ( VERB .EQ. 'SLOPE') THEN
            CALL FFCHAR (IFLD, INTYP, CFIELD, 'TOP', VERB)
            IF (MATSTR(VERB, 'TOP', 1) .OR.
     &           MATSTR(VERB, 'FRONT', 1)) THEN
               CALL FFREAL (IFLD, INTYP, RFIELD,
     &              'X slope at bottom end', 0.0, SLTOP(1), *10)
               CALL FFREAL (IFLD, INTYP, RFIELD,
     &              'Y slope at bottom end', 0.0, SLTOP(2), *10)
            END IF 
            
         ELSE IF (VERB .EQ. 'LIST') THEN
            CALL SHOCMD ('COMMANDS', CMDTBL)
         END IF
      ELSE IF (NUMFLD .GE. 2) THEN
         IPT = IPT + 1
         IF (IPT .GT. NTOT) THEN
            NTOT = NTOT + NDEFS
            CALL MDLONG ('ZSPL', KZSPL, NTOT)
            CALL MDLONG ('XSPL', KXSPL, NTOT)
            CALL MDLONG ('YSPL', KYSPL, NTOT)
            CALL MDSTAT (NERR, MEM)
            IF (NERR .GT. 0) THEN
               CALL MEMERR
               STOP 'Memory Allocation in GETSPL'
            END IF
         END IF
         A(KZSPL + IPT - 1) = RFIELD(1)
         A(KXSPL + IPT - 1) = RFIELD(2)
         A(KYSPL + IPT - 1) = RFIELD(3)
      END IF
      GO TO 10
      
C     ... Done reading data, compress arrays and allocate remaining arrays
      
   20 CONTINUE
      CALL MDLONG ('ZSPL',  KZSPL, IPT)
      CALL MDLONG ('XSPL',  KXSPL, IPT)
      CALL MDLONG ('YSPL',  KYSPL, IPT)
      
      CALL MDRSRV ('XSPL2', KXSPL2, IPT)
      CALL MDRSRV ('YSPL2', KYSPL2, IPT)
      CALL MDRSRV ('SCR',   KSCR,   IPT)
      
      CALL MDSTAT (NERR, MEM)
      IF (NERR .GT. 0) THEN
         CALL MEMERR
         STOP 'Memory Allocation in GETSPL'
      END IF
      
      NSPLT = IPT
      
      RETURN
      END
