#include <stdio.h>
#include <stdlib.h>
#include <gccore.h>
#include <wiiuse/wpad.h>
#include "tools.h"

#define MAGIC1 0x81001EC8
#define MAGIC2 0x00000000

static void *xfb = NULL;
static GXRModeObj *rmode = NULL;

int main(int argc, char **argv)
{
	/* Console initialization */
	VIDEO_Init();
	WPAD_Init();
	PAD_Init();
	rmode = VIDEO_GetPreferredMode(NULL);
	xfb = MEM_K0_TO_K1(SYS_AllocateFramebuffer(rmode));
	console_init(xfb,20,20,rmode->fbWidth,rmode->xfbHeight,rmode->fbWidth*VI_DISPLAY_PIX_SZ);
	VIDEO_Configure(rmode);
	VIDEO_SetNextFramebuffer(xfb);
	VIDEO_SetBlack(FALSE);
	VIDEO_Flush();
	VIDEO_WaitVSync();
	if(rmode->viTVMode&VI_NON_INTERLACE) VIDEO_WaitVSync();
	printf("\x1b[2;0H");
	/* Console initialization */

	/* Print some text on the screen and wait for a buttonpress */
	printf("MAGIC1 fixer by Mr. eXoDia\n\nThis program fixes the anti-piracy feature of the IOS236 installer!!!\n\n");
	printf("My story:\nThe DVD-reader of my WII somehow F*CK*D up and I\nthought that I had to buy a new WII But in a search\non the internet I found the homebrew channel.\nI found out that you can play backups from an USB\ndrive. But when I wanted to install the costum\nIOS236 my little brother (4years old) pressed some\nbuttons and before I knew it I was a 'pirate' I\nlooked everywhere but the only fix was entering a\nnon-pirated game in the drive and play it. The author\nof the cIOS236 installer included the source code\nin his package and I found a way to patch it :)\n\n");
	set_highlight(true);
	printf("ONLY USE THIS SOFTWARE IF YOU HAVE THE SAME PROBLEM AS ME, ELSE JUST BUY A GAME AND INSERT IT!!!!!\n\n");
	set_highlight(false);
	printf("Press any key to continue...\n\n");
	waitforbuttonpress(NULL, NULL);

	*((int *)MAGIC1) = MAGIC2;
	if(*((int *)MAGIC1) == MAGIC2)
	{
		printf("Address at 0x81001EC8 is patched!\nYou should try to run the IOS236 installer now\n\n");
	}
	else
	{
		printf("Unknown error\nMaybe the memory at 0x81001EC8 is write-protected\n\n");
	}
	printf("Press any key to reboot the WII...\n");
	waitforbuttonpress(NULL, NULL);

	Reboot(); //Restart the WII

	return 0;
}
