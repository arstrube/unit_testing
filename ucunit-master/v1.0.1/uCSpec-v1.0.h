/*****************************************************************************
 *                                                                           *
 *  UcSpec - Support for behavior-driven development (specification by       *
 *           example) for uCUnit                                             *
 *                                                                           *
 *  (C) 2014  Arnd R. Strube                                                 *
 *            https://www.ucunit.org                                         *
 *                                                                           *
 *  File        : uCSpec-v1.0.h                                              *
 *  Description : Macros to support BDD for Unit-Testing                     *
 *  Author      : Arnd R. Strube                                             *
 *  Contact     : www.ucunit.org                                             *
 *                                                                           *
 *****************************************************************************/

/*
 * This file is part of ucUnit.
 *
 * You can redistribute and/or modify it under the terms of the
 * Common Public License as published by IBM Corporation; either
 * version 1.0 of the License, or (at your option) any later version.
 *
 * uCUnit is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * Common Public License for more details.
 *
 * You should have received a copy of the Common Public License
 * along with uCUnit.
 *
 * It may also be available at the following URL:
 *       http://www.opensource.org/licenses/cpl1.0.txt
 *
 * If you cannot obtain a copy of the License, please contact the
 * author.
 */

#ifndef UCSPEC_0101_H_
#define UCSPEC_0101_H_

/*****************************************************************************/
/* Variables */
/*****************************************************************************/

static int ucspec_testcases_todo = 0; /* Number of specs not yet implemented */
static int ucunit_line = 0;           /* Used to detect empty specifications */

/*****************************************************************************/
/* Support behavior-driven development (specification by example             */
/*****************************************************************************/

/**
 * @Macro:       DESCRIBE()
 *
 * @Description: Macro to support behavior-driven test description
 *               (to a certain degree).
 *
 * @Remarks:     This is gleaned from CSpec. It does not use the UCUNIT
 *               prefix, because - well that would kind of spoil it.
 *
 */
#define DESCRIBE(caption)                                            \
    UCUNIT_WriteString("Describe: " caption "\n");                    \
    {

/**
 * @Macro:       DESCRIBE_END
 *
 * @Description: Macro to support behavior-driven test description
 *               (to a certain degree).
 *
 * @Remarks:     This is gleaned from CSpec. It does not use the UCUNIT
 *               prefix, because - well that would kind of spoil it.
 *
 */
#define DESCRIBE_END                                                 \
        UCUNIT_WriteString("\n");                                    \
    }

/**
 * @Macro:       IT()
 *
 * @Description: Macro to mark the beginning of a specification in
 *               behavior-driven development (specification by example).
 *
 * @Remarks:     Wraps UCUNIT_TestcaseBegin(name)
 *
 */
#define IT(caption)                                                  \
    {                                                                \
        ucunit_line = __LINE__;                                      \
        UCUNIT_TestcaseBegin(caption);                               \
        {

/**
 * @Macro:       IT_END
 *
 * @Description: Macro to mark the end of a specification
 *               If no code is specified for the specification, then
 *               it will automatically be treated as NOT IMPLEMENTED.
 *
 * @Remarks:     Syntactic sugar - wraps UCUNIT_TestcaseBegin(name)
 *
 */
#define IT_END                                                       \
        }                                                            \
        if(ucunit_line + 1 >= __LINE__) { /* allow on following line */ \
            ucspec_testcases_todo++;                                 \
            UCUNIT_WriteString(" N O T   I M P L E M E N T E D\n");  \
        }                                                            \
        else UCUNIT_TestcaseEnd();                                   \
    }

/* Syntactic sugar ***********************************************************/
#define SHOULD(condition, msg, args) UCUNIT_Check(condition, msg, args)
#define SHOULD_EQ(expected, actual) UCUNIT_CheckIsEqual(expected, actual)
#define SHOULD_BE_NULL(pointer) UCUNIT_CheckIsNull(pointer)
#define SHOULD_NOT_BE_NULL(pointer) UCUNIT_CheckIsNotNull(pointer)
#define SHOULD_BE_IN_RANGE() UCUNIT_CheckIsInRange(value, lower, upper)
#define SHOULD_BE_8BIT(value, lower, upper) UCUNIT_CheckIs8Bit(value)
#define SHOULD_BE_16BIT(value) UCUNIT_CheckIs16Bit(value)
#define SHOULD_BE_32BIT(value) UCUNIT_CheckIs32Bit(value)
#define SHOULD_BE_BITSET(value) UCUNIT_CheckIsBitSet(value, bitno)
#define SHOULD_BE_BITCLEAR(value, bitno) UCUNIT_CheckIsBitClear(value, bitno)

/*****************************************************************************/
/* uCSpec Replacement Testsuite Summary                                      */
/*****************************************************************************/

/**
 * @Macro:       UCUNIT_WriteSummary()
 *
 * @Description: Writes the test suite summary.
 *
 * @Remarks:     This macro uses UCUNIT_WriteString(msg) and
 *               UCUNIT_WriteInt(n) to write the summary.
 *
 */
//#undef UCUNIT_WriteSummary()
#define UCSPEC_WriteSummary()                                       \
{                                                                   \
    UCUNIT_WriteString("\n**************************************"); \
    UCUNIT_WriteString("\nSpecs not implemented: ");                \
    UCUNIT_WriteInt(ucspec_testcases_todo);                         \
    UCUNIT_WriteSummary();                                          \
}

#endif /*UCSPEC_H_*/
