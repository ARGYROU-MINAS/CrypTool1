#! perl -w

# Skript, dass die automatisch mit makehm.exe erstellte Datei NumberShark.hm HtmlHelp-kompatibel konvertiert zu NumberShark_helpIDs.h
# 	- in .h umbenennen
# 	- #define statements allen HIDs voranstellen

# aktuelles Hilfeverzeichnis
$lang=$ARGV[0];

$helpdir ="sharkHelp_".$lang;

# die .hm Datei ?ffnen
open(HMFILE, "< $helpdir/NumberShark.hm") or die "Couldn't open $helpdir/NumberShark.hm for reading: $!\n";

# die .h Datei erzeugen oder zum ?berschreiben ?ffnen
open(HFILE, "> $helpdir/NumberShark_helpIDs.h") or die "Couldn't open $helpdir/NumberShark_helpIDs.h for writing: $!\n";

# Zeilen in der .hm Datei mit HID erkennen und in .h Datei mit vorangestelltem #define schreiben

while(defined($line = <HMFILE>))    
	{
		if($line =~ /HID/) 	# falls HID in der Zeile vorkommt, wird #define vorangestellt 
					# falls nicht wird Zeile ohne Ver?nderung ?bernommen
			{
				print HFILE "#define ".$line;				
			}
		else
			{
				print HFILE $line;
			}		
	}
close(HMFILE);
close(HFILE);

