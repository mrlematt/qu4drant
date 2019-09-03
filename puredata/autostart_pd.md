<h2>autostart pd on raspbian</h2>

I struggled to find a clean way to launch pd on startup.<br/>

Disclaimer: I don't understand <i>why</i> this works :) 

<h3>method 1 (tested - worked on one raspi... but failed on the last ones because LXDE was killing PD on startup)</h3>

<ul>
<li>create the <code>/bin</code> folder. <code>mkdir ./</code></li>
<li>enter the bin folder ( ./pi/bin/ ) <code>cd ./bin</code></li>
<li>create a pd startup script: <code>sudo nano pd_startup</code> 
</li>

<li>add those lines <br/>
  <code>pd -alsamidi -midiindev 1 /home/pi/Documents/pd/mainpatch.pd & sleep 5</code>
  <br/>
  <code>aconnect 'Teensy MIDI:0' 'Pure Data:0' & sleep 5 </code>
</li>

<li>then ctrl+x and "y" then enter to save and quit nano.</li>

<li>make the script executable:<code>sudo chmod 755 pd_startup</code></li>

<li>then <code>sudo nano /etc/profile</code> <br/>

add this at the end of the file: <br/>

<code>/home/pi/bin/pd_startup</code>
</li>
then ctrl+x and "y" then enter to save and quit nano.

</ul>

<br/>
then reboot. your pd patch should be there running. midi should be received from the teensy into pure data.
<br/>

<h3>method 2 - tested</h3>

<ul>
  <li>open terminal <code> sudo nano pdstartup.sh</code> creates an empty script</li>
  <li>type <code>#!/bin/bash</code></li>
  <li>type <code>sleep 10</code> <br/><code>pd -alsamidi -midiindev 1 /home/pi/Documents/pd/mainpatch.pd & sleep 5</code>
  <br/>
  <code>aconnect 'Teensy MIDI:0' 'Pure Data:0' & sleep 5 </code></li>
  <li>ctrl + X, then Y, then enter</li>
  <li>open terminal <code>sudo chmod +x mypatch.pd</code></li>
  <br/>
  you just created a script launching your patch.
  <br/>
  
  <li>open terminal<code>sudo nano /etc/xdg/lxsession/LXDE-pi/autostart</code></li>
  <li>go to last line, type <code>@sh /home/pi/pdstartup.sh</code></li>
  <li>ctrl + X, Y and enter</li>
  <li>do a reboot</li>
  it should launch the patch, initialize the midi stuff.
  <br/>
  <b>problem:</b> as soon as you touch the pd window, it kills the pd app... it may be related to dsp priority stuff.
  to try: 
  <a>The priority message you get has to do with the priority Pd is trying to get and the actual priority it does get from the kernel. You haven't specified the priority, so try to do that.</a>
<a>First of all add user pi to the audio group by writing this to a terminal:</a>

<code>sudo usermod -a -G audio pi</code>
Then edit the /etc/security/limits.conf file by typing:
<code>sudo nano /etc/security/limits.conf</code>
The file will open in the nano editor (inside the terminal). 
Navigate to the end of it with the arrow keys and add the following:
<code>@audio - rtprio 95
@audio - memlock unlimited </code>
Optionally add the following line too:
<code>@audio - nice -19</code>

Try launching Pd again. You shouldn't launch Pd with sudo, but as user pi. You should just set your system so that the user pi can get the desired priority.
  
 
</ul>



