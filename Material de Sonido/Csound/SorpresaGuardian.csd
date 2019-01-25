<CsoundSynthesizer>
<CsOptions>
; Select audio/midi flags here according to platform
-W -o Sorpresa.wav
;-iadc    ;;;uncomment -iadc if realtime audio input is needed too
; For Non-realtime ouput leave only the line below:
; -o oscil.wav -W ;;; for file output any platform
</CsOptions>
<CsInstruments>

sr = 44100
ksmps = 32
nchnls = 2
0dbfs  = 1

instr 1



kamp = .4
kenv linen .4, .1, 1.03, .8 
asig oscil kenv*kamp, cpspch(9), 1 
 
kamd = .6
kend linen .4, .1, 1.03, .8 
asid oscil kend*kamd, cpspch(6), 4  

kam = .8
ken linen .8, .1, 1.03, .8 
adel oscil ken * kam, cpspch(6), 1  

;kre expon 6.4, .4, 4.4 ;para conseguir un efecto distinto cambiar
;kcp =  cpspch(kre) 	  ;frequency

     outs asig+asid+adel, asig+asid+adel

endin
</CsInstruments>
<CsScore>
f1 0 16384 10 1                                          ; Sine
f2 0 16384 10 1 0.5 0.3 0.25 0.2 0.167 0.14 0.125 .111   ; Sawtooth
f3 0 16384 10 1 0   0.3 0    0.2 0     0.14 0     .111   ; Square
f4 0 16384 10 1 1   1   1    0.7 0.5   0.3  0.1          ; Pulse
;ins 	ini 	dur  tabla 
;-------------------------------------------------------
i  1 	0  		1.05    4	
e
</CsScore>
</CsoundSynthesizer>
<bsbPanel>
 <label>Widgets</label>
 <objectName/>
 <x>100</x>
 <y>100</y>
 <width>320</width>
 <height>240</height>
 <visible>true</visible>
 <uuid/>
 <bgcolor mode="nobackground">
  <r>255</r>
  <g>255</g>
  <b>255</b>
 </bgcolor>
</bsbPanel>
<bsbPresets>
</bsbPresets>
