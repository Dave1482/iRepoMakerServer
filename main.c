// Repo Maker Server, based on Mongoose Server by valetok, made into a command and modified by Dave1482

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>
#include <math.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <CoreFoundation/CoreFoundation.h>
#include "mongoose.h"
#define ERROR(x) \
fprintf(stderr, "[Error] " x); \
exit(EXIT_FAILURE);
bool portMode = false;
bool customPort = false;
char *port;
int c;
bool startMode = false;
bool helpMode = false;
struct mg_context *ctx;
static void startServer();
static void print_usage(char *progname);

static void startServer()
{
ctx = mg_start ();
mg_set_option (ctx, "root", "/var/root/Library/RepoMaker/./");
mg_set_option (ctx, "ports", port);
mg_set_option (ctx, "cgi_interp", "/usr/bin/RepoMaker/iUpload");
mg_set_option (ctx, "index_files", "README.html,index.html,index.php");

char baseHostName[255];
gethostname (baseHostName, 255);
char hn[255];
sprintf (hn, "%s.local", baseHostName);
struct hostent *host = gethostbyname (hn);
if (host == NULL) {
herror ("resolv");
printf("Failed To Start, exiting...\n");
exit(-1);
} else {
struct in_addr **list = (struct in_addr **)host->h_addr_list;
printf("Started Server! URLs:\nhttp://%s:%s/\nhttp://%s.local:%s/\nLocal URLs:\nhttp://127.0.0.1:%s/\nhttp://localhost:%s/\n", inet_ntoa (*list[0]), port, baseHostName, port, port, port);
CFRunLoopRun();
}
}

static void print_usage(char *progname)
{
printf("Repo Maker Server 1.0\nUsage: %s <options>\nOptions include:\n", progname);
printf("\t-b:\tBegin Server.\n");
printf("\t-p [port]:Set Port (Use Numbers Only!).\n");
printf("\tRunning \"killall RepoMakerServer\" as root:\tEnd Server.\n");
printf("\t-h:\tShow this help.\n");
}

int main(int argc, char *argv[])
{
if (argc < 2) {
printf("Must specify either -b or -h.\n");
return -1;
}

while ((c = getopt(argc, argv, "bph")) != -1) {
switch (c) {
case 'b':
startMode = true;
portMode = true;
break;
case 'p':
if (argv[optind]) { 
port = argv[optind];
} else { 				printf("No port was specified. Using default (1482).\n");
port = "1482";
} 
customPort = true;
break;

case 'h':
helpMode = true;
break;
default:
printf("Must specify either -b or -h.\n");
return -1;
}
}
if (helpMode) {
print_usage(argv[0]);
return 0;
}
if (!helpMode && !startMode) {
printf("Must specify either -b or -h.\n");
return -1;
}
if (portMode == true && customPort == false) {
port = "1482";
}
if (startMode) {
startServer();
}
return 0;
}
