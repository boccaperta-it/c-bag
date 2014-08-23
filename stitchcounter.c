#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

/* stitchcounter: useful tool to help knitting and crocheting
 * usage:
 * - first option: specify original gauge
 *                 specify your gauge
 *                 specify how many values you need
 *                 calculate: x = (my_rows * value) / org_rows
 *                 calculate: x = (my_sts * value) / org_sts
 * - second option: specify your gauge: rows and stitches
 *                  specify how many values you need
 *                  specify cm for each value
 *                  calculate the number of stitches/rows needed for the value */

#define CM_PER_SQUARE 10.0
#define MAX_LINELENGTH 4096
#define MAX_ATTEMPTS 10

static float get_number(const char *prompt)
{
    float value;
    char line[MAX_LINELENGTH];
    int count = 0;
    while (fputs(prompt, stdout) != EOF &&
           fgets(line, sizeof(line), stdin) != 0) {
        if (sscanf(line, "%f", &value) == 1)
            return value;
        if (count++ > MAX_ATTEMPTS) {
            printf("I give in; I don't understand what you're typing\n");
            exit(1);
        }
	printf("value must be a number (es.: 1, 0.1, 20.3, etc.)\n");
    }

    printf("oops: I got EOF or an error; goodbye!\n");
    exit(1);
}

static char get_char(const char *prompt)
{
    char value;
    char line[MAX_LINELENGTH];
    int count = 0;
    while (fputs(prompt, stdout) != EOF &&
           fgets(line, sizeof(line), stdin) != 0) {
        if (sscanf(line, "%s", &value) == 1) {
	    if (!isalpha(value)) {
		printf("value must be either [r] or [s]\n");
	    } else {
		return value;
	    }
	}
        if (count++ > MAX_ATTEMPTS) {
            printf("I give in; I don't understand what you're typing\n");
            exit(1);
        }
	printf("value must be either [r] or [s]\n");
    }

    printf("oops: I got EOF or an error; goodbye!\n");
    exit(1);
}

int opt1()
{
    float rows, sts, org_rows, org_sts, org_val;
    int values;

    printf("original gauge\n");
    org_rows = get_number("\tplease enter the number of rows: ");
    org_sts = get_number("\tplease enter the number of stitches: ");

    printf("your gauge\n");
    rows = get_number("\tplease enter the number of your rows: ");
    sts = get_number("\tplease enter the number of your stitches: ");

    values = get_number("how many values do you need? ");

    int i;
    for (i = 1; i <= values; i++) {
	char sel = get_char("is value rows [r] or stitches [s]? ");
	switch(sel) {
	    case 'r':
   	        org_val = get_number("please enter the rows of the original project: ");
	        printf("your final result is: %3.1f\n", (rows * org_val) / org_rows);
	        break;
	    case 's':
		org_val = get_number("please enter the stitches of the original project: ");
	        printf("your final result is: %3.1f\n", (sts * org_val) / org_sts);
		break;
  	    default:
  	        printf("i don't understand your input\n");
	        break;
	}
    }
    return 0;
}

int opt2()
{
    float rows, sts, rows1cm, sts1cm, cm;
    int values;

    printf("your gauge\n");
    rows = get_number("\tplease enter the number of your rows: ");
    sts = get_number("\tplease enter the number of your stitches: ");

    rows1cm = rows / CM_PER_SQUARE;
    sts1cm = sts / CM_PER_SQUARE;

    values = get_number("how many values do you need? ");

    int i;
    for (i = 1; i <= values; i++) {
	char sel = get_char("is value rows [r] or stitches [s]? ");
	switch(sel) {
	    case 'r':
		cm = get_number("please enter the cms of your project: ");
	        printf("your final result is: %3.1f\n", (rows1cm * cm));
	        break;
	    case 's':
		cm = get_number("please enter the cms of your project: ");
	        printf("your final result is: %3.1f\n", (sts1cm * cm));
		break;
  	    default:
  	        printf("i don't understand your input\n");
	        break;
	}
    }
    return 0;
}

main()
{
    int opt;

    printf("\nstitchcounter: useful tool to help knitting and crocheting\n\n");
    printf("options:\n");
    printf("\t1) calculate stitches from original gauge\n");
    printf("\t2) calculate stitches from dimensions\n");
    opt = get_number("pick your option: ");

    switch(opt) {
        case 1:
            opt1();
	    break;
        case 2:
            opt2();
	    break;
        default:
            printf("option must be 1 or 2\n");
	    break;
    }

    return 0;
}
