#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

/* inchcmconverter: converts from inch to cm and viceversa */

#define INCH_TO_CM 2.54 // 1 inch is 2.54 cm
#define CM_TO_INCH 0.39 // 1 cm is 0.39 inch
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

inch_to_cm()
{
   float inch = get_number("please enter the inches: ");
   printf("%3.2f inches are %3.2f cms\n", inch, (inch * INCH_TO_CM));
}

cm_to_inch()
{
   float cm = get_number("please enter the cms: ");
   printf("%3.2f cms are %3.2f inches\n", cm, (cm * CM_TO_INCH));
}

main()
{
    int opt;

    printf("\ninchcmconverter: converts from inch to cm and viceversa\n\n");
    printf("options:\n");
    printf("\t1) from inch to cm\n");
    printf("\t2) from cm to inch\n");
    opt = get_number("pick your option: ");

    switch(opt) {
        case 1:
            inch_to_cm();
	    break;
        case 2:
            cm_to_inch();
	    break;
        default:
            printf("option must be 1 or 2\n");
	    break;
    }

    return 0;
}
