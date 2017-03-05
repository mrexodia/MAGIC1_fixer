#include <sys/unistd.h> //for usleep
#include <wiiuse/wpad.h> //For the pad

void Reboot();
void waitforbuttonpress(u32 *out, u32 *outGC);
void set_highlight(bool highlight);

