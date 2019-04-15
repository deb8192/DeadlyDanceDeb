<CsoundSynthesizer>
<CsOptions>
; Select audio/midi flags here according to platform
-W -o Soltar.wav
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



ifn  = p4
kres expon 4.6, .4, 4.5 ;para conseguir un efecto distinto cambiar
kcps =  cpspch(kres/1.1)  ;frequency

kamp = .2
kenv adsr .01, .02, .1, .1 
asig oscil kenv * kamp, kcps, ifn
aret	delay   asig, .05   

kam = .2
ken adsr .02, .005, .01, .01 
asen oscil ken * kam, kcps, ifn
adel	delay   asen, .12   

     outs aret+adel , aret+adel
     
;no del todo pero mas o menos se consigue efecto cartoon coger objetos

endin
</CsInstruments>
<CsScore>
f1 0 16384 10 1                                          ; Sine
f2 0 16384 10 1 0.5 0.3 0.25 0.2 0.167 0.14 0.125 .111   ; Sawtooth
f3 0 16384 10 1 0   0.3 0    0.2 0     0.14 0     .111   ; Square
f4 0 16384 10 1 1   1   1    0.7 0.5   0.3  0.1          ; Pulse
;ins 	ini 	dur  tabla 
;-------------------------------------------------------
i  1 	0  		.2    4	
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
