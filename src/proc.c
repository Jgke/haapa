#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include "proc.h"
#include "config.h"
#include "result.h"

Result *proc_load(char *str) {
	FILE *f;
	Result *res;
	res = init_res();
	float loads[3];
	int val;
	int loadtime = atoi(str);

	f = fopen("/proc/loadavg", "r");

	if(f == NULL) {
		res->error=1;
		return res;
	}

	val = fscanf(f, "%f %f %f", &loads[0], &loads[1], &loads[2]);
	fclose(f);
	if(val == EOF) {
		res->error=1;
		return res;
	}

	if(loadtime != 3)
		sprintf(res->string, "%.2f", loads[loadtime]);
	else
		sprintf(res->string, "%.2f %.2f %.2f", loads[0], loads[1], loads[2]);

	return res;
}

Result *proc_memory() {
	FILE *f;
	Result *res;
	res = init_res();
	char u[9][16];
	int mem_total, mem_free, mem_buffers, mem_cached, mem_used, val;

	f = fopen("/proc/meminfo", "r");

	if(f == NULL) {
		res->error=1;
		return res;
	}

	val = fscanf(f, "%s %i %s %s %i %s %s %i %s %s %i %s", 
		u[0], &mem_total, u[1],
		u[2], &mem_free, u[3],
		u[4], &mem_buffers, u[5],
		u[6], &mem_cached, u[7]);
	fclose(f);

	if(val == EOF) {
		res->error=1;
		return res;
	}

	mem_used = mem_total - mem_free - mem_buffers - mem_cached;

	sprintf(res->string, "%i/%i MB", mem_used/1024, mem_total/1024);
	res->value=mem_used;
	res->max=mem_total;
	return res;
}


float cpu_prev_total = 0;
float cpu_prev_idle = 0;

Result *proc_cpu() {
	FILE *f;
	Result *res;
	res = init_res();
	float total = 0;
	float idle = 0;
	int i;
	int val;
	float usage;
	float diff_idle;
	float diff_total;

	char ident[5];

	int a[7];

	f = fopen("/proc/stat", "r");

	if(f == NULL) {
		res->error=1;
		return res;
	}

	val = fscanf(f, "%s %i %i %i %i %i %i %i", 
		ident, &a[0], &a[1], &a[2], &a[3], &a[4], &a[5], &a[6]);
	fclose(f);

	if(val == EOF) {
		res->error=1;
		return res;
	}

	idle = a[3];

	for(i = 0; i < 7; i++) {
		total += a[i];
	}

	if(cpu_prev_total > 0) {
		diff_idle = idle - cpu_prev_idle;
		diff_total = total - cpu_prev_total;
		usage = 100 * (diff_total - diff_idle) / diff_total;
		res->value = usage;
		res->max = 100;
		sprintf(res->string, "%.0f%%", usage);
	}else{
		strcpy(res->string, "");
		res->value=0;
		res->max=100;
	}

	cpu_prev_total = total;
	cpu_prev_idle = idle;

	return res;
}

Result *proc_uptime() {
	FILE *f;
	Result *res;
	res = init_res();
	float uptime = 0;
	int val;

	f = fopen("/proc/uptime", "r");

	if(f == NULL) {
		res->error=1;
		return res;
	}

	val = fscanf(f, "%f", &uptime);
	fclose(f);

	if(val == EOF) {
		res->error=1;
		return res;
	}

	res->value = uptime;

	return res;
}

Result *proc_cpu_mhz() {
	FILE *f;
	Result *res;
	char* match;
	char buffer[1024];
	float mhz;
	res = init_res();

	f = fopen("/proc/cpuinfo", "r");

	if(f == NULL) {
		res->error=1;
		return res;
	}

	fread(buffer, 1, sizeof (buffer), f);

	fclose(f);

	match = strstr(buffer, "cpu MHz");

	if(match == NULL) {
		res->error=1;
		return res;
	}

	sscanf (match, "cpu MHz  :  %f", &mhz);

	res->value = mhz;

	sprintf(res->string, "%i MHz", (int)mhz);

	return res;
}
