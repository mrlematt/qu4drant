<h2>autostart pd on raspbian</h2>

I struggled to find a clean way to launch pd on startup.<br/>

Disclaimer: I don't understand <i>why</i> this works :) 

<h3>method 1 (tested - works)</h3>

<ul>
<li>create the <code>/bin</code> folder. <code>mkdir ./</code></li>
<li>enter the bin folder ( ./pi/bin/ ) <code>cd ./bin</code></li>
<li>create a pd startup script: <code>sudo nano pd_startup</code> 
</li>

<li>add those lines <code>pd -alsamidi -midiindev 1 /home/pi/Documents/pd/mainpatch.pd & sleep 5</code><br/>
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
then reboot. your pd patch should be there running.
<br/>

<h3>method 2</h3>

<ul>
  <li>open terminal <code> sudo nano pdstartup.sh</code> creates an empty script</li>
  <li>type <code>#!/bin/bash</code></li>
  <li>type <code>/home/pi/Desktop/mypatch.pd</code> with the path to your patch</li>
  <li>ctrl + X, then Y, then enter</li>
  <li>open terminal <code>sudo chmod +x mypatch.pd</code></li>
  <br/>
  you just created a script launching your patch. congrats.
  <br/>
  
  <li>open terminal<code>sudo nano /home/pi/.config/lxsession/LXDE-pi/autostart</code></li>
  <li>go to last line, type <code>@sh /home/pi/pdstartup.sh</code></li>
  <li>ctrl + X, Y and enter</li>
  <li>do a reboot</li>
  
  
  
</ul>



