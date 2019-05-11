<h2>autostart pd on raspbian</h2>

I struggled to find a clean way to launch pd on startup.<br/>

Disclaimer: I don't understand <i>why</i> this works :) 

<h3>method 1</h3>

<ul>
<li>create the <code>/bin</code> folder. <code>mkdir ./</code></li>
<li>enter the bin folder ( ./pi/bin/ ) <code>cd ./bin</code></li>
<li>create a pd startup script: <code>sudo nano pd_startup</code> 
</li>

<li>add this line <code>pd /home/pi/Documents/pd/mainpatch.pd & </code></li>

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



