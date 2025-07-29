
; Happens whenever the CPU is idle and that somehow the cpuhalt loop got escaped
cpu_idle_alternative:
	hlt 
	jmp cpu_idle_alternative