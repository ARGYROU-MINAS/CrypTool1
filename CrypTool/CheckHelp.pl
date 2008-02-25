# CheckHelp.pl
#
# This script does a variety of consistency checks for the online help 
# of the CrypTool project. 
#
# Initially, the script locates all existing help files within the help 
# directory and parses the CrypTool resource file for resource identifiers. 
# Afterwards, this information is processed in a single consistency check.
#
# INVOCATION
#
#   perl CheckHelp.pl [LANGUAGE] [HELP DIRECTORY] [[DEBUG]]
#
# EXAMPLES
#
#   perl CheckHelp.pl GERMAN hlp_de
#   perl CheckHelp.pl ENGLISH hlp_en DEBUG
#   perl CheckHelp.pl POLISH hlp_pl DEBUG
#
# DETAILED DESCRIPTION
#
#   todo...
#
#
# 
# Florian Marchal, 02/22/2008 (florian@marchal.de)
# 
#
#


use strict;
use File::Find;
use HTML::LinkExtor;

# variables
my %dialogIdentifiers = ();
my %menuIdentifiers = ();
my %helpFiles = ();
my %helpFilesHTML = ();
my $helpDirectory = ();
my %possibleLinks = ();

# some more variables
my $language = $ARGV[0] || 0;
my $helpDirectory = $ARGV[1] || 0;
my $resourceFile = "CrypTool.rc";
my $debug = $ARGV[2] || 0;

# remove trailing slash from help directory, if necessary
$helpDirectory =~ s/\/$//;

# collect all help files in the help file directory
collectHelpFiles($helpDirectory);
# collect all dialog identifiers in the resource file
collectDialogIdentifiers($language);
# collect all menu identifiers in the resource file
collectMenuIdentifiers($language);

# run the consistency check
runConsistencyCheck($language, $helpDirectory);



#
# ***************************************************************************
# *** SUB FUNCTIONS *********************************************************
# ***************************************************************************
#

# This callback function finds all kinds of help files
sub callbackFindHelpFiles() {
    if("\L$File::Find::name" =~ /\.html$/ ||
       "\L$File::Find::name" =~ /\.htm$/ ||
       "\L$File::Find::name" =~ /\.gif$/ ||
       "\L$File::Find::name" =~ /\.jpg$/ || 
       "\L$File::Find::name" =~ /\.png$/ ||
       "\L$File::Find::name" =~ /\.css$/ || 
       "\L$File::Find::name" =~ /\.txt$/ ||
       "\L$File::Find::name" =~ /\.pdf$/ ||
       "\L$File::Find::name" =~ /\.js$/ ) {
        my $lowercasename = "\L$File::Find::name";
        $lowercasename =~ s/\\/\//g; # windows?
        # add file to regular help file pool
        ${$helpFiles{$helpDirectory}}{"$lowercasename"} = "FOUND";
        # add file to .html help file pool, if necessary
        if($lowercasename =~ /\.html$/) {
            ${$helpFilesHTML{$helpDirectory}}{"$lowercasename"} = "FOUND";
        }
    }
}

# This function collects all help files for the 
# help directory given as parameter (i.e. "hlp_de")
sub collectHelpFiles() {
    $helpDirectory = shift;
    find(\&callbackFindHelpFiles, $helpDirectory);
}

# This function collects all dialog identifiers for 
# the language given as parameter (i.e. "GERMAN") 
sub collectDialogIdentifiers() {
    my $language = shift;
    my $ignore = 1;
    my $found = 0;
    open(FILE, $resourceFile) or die ("Opening $resourceFile: $!\n");
    my @fileArray = <FILE>;
    foreach my $line(@fileArray) {
        if($line =~ /^LANGUAGE\s+LANG_$language,/) {
          $ignore = 0;
          $found = 1;
          next;
        }
        if($ignore == 0) {
            if($line =~ /^LANGUAGE\s+LANG_/) {
                $ignore = 1;
                next;
            } 
            if($line =~ /^([a-zA-Z0-9_]+)\s+DIALOG/) {
                push(@{$dialogIdentifiers{$language}}, $1);
            }
        }
    }
    if($found == 0) {
        print "  WARNING: dialog identifiers for language \"$language\" could not be found\n" if($debug);
    }
    close(FILE);
}

# This function collects all menu identifiers for
# the language given as parameter (i.e. "GERMAN")
sub collectMenuIdentifiers() {
    my $language = shift;
    my $ignore = 1;
    my $found = 0;
    my $menu = 0;
    my $depth = 0;
    open(FILE, $resourceFile) or die ("Opening $resourceFile: $!\n");
    my @fileArray = <FILE>;
    foreach my $line(@fileArray) {
        if($line =~ /^LANGUAGE\s+LANG_$language,/) {
          $ignore = 0;
          $found = 1;
          next;
        }
        if($ignore == 0) {
            if($line =~ /^LANGUAGE\s+LANG_/) {  
                $ignore = 1;
                next;
            }
            if($line =~ /^IDR_MAINFRAME\s+MENU\s+$/) {
                $menu = 1;
            }
            if($line =~ /^END\s+$/ && $menu == 1 && $depth == 0) {
                $menu = 0;
            }
            # at this point we are within the desired menu; now try to 
            # identify all menu item identifiers that need a help file
            if($line =~ /MENUITEM\s+[^,]+,\s+([a-zA-Z0-9_]+)/) {
                push(@{$menuIdentifiers{$language}}, $1);
            }
        }
    }
    if($found == 0) {
        print "  WARNING: menu identifiers for language \"$language\" could not be found\n" if($debug);
    }
    close(FILE);
}

# This function checks if there is a valid .html help file for 
# each identifier found in the resource file; furthermore, this 
# function checks all .html help files for dead links; the first 
# parameter is the language, the second parameter is the help 
# directory (i.e. "GERMAN" and "hlp_de")
sub runConsistencyCheck() {
    my $language = shift;
    my $directory = shift;

    my $numberOfMissingDialogIdentifiers = 0;
    my $numberOfMissingMenuIdentifiers = 0;
    my $numberOfDeadLinks = 0;

    if(not defined $helpFilesHTML{$directory}) {
        die "ABORTING: there seem to be no .html help files in directory $directory\n";
    }

    my %hashHTMLHelpFiles = %{$helpFilesHTML{$directory}};

    # check help files for dialog identifiers
    if(defined $dialogIdentifiers{$language}) {
        my @arrayDialogIdentifiers = @{$dialogIdentifiers{$language}};
        print "Checking help files for dialogs (language \"$language\")\n" if($debug);
        foreach(@arrayDialogIdentifiers) {
            my $identifier = $_;
            my $filename = "\L$helpDirectory/h$identifier.html";
            if(not defined $hashHTMLHelpFiles{$filename}) {
                print "  WARNING: $filename seems to be missing (dialog identifier is $identifier)\n" if($debug);
                $numberOfMissingDialogIdentifiers++;
            }
        }
    }
    
    # check help files for menu identifiers
    if(defined $menuIdentifiers{$language}) {
        my @arrayMenuIdentifiers = @{$menuIdentifiers{$language}};
        print "Checking help files for menu items (language \"$language\")\n" if($debug);
        foreach(@arrayMenuIdentifiers) {
            my $identifier = $_;
            my $filename = "\L$helpDirectory/h$identifier.html";
            if(not defined $hashHTMLHelpFiles{$filename}) {
                print "  WARNING: $filename seems to be missing (menu identifier is $identifier)\n" if($debug);
                $numberOfMissingMenuIdentifiers++;
            }
        }
    }

    # check for (possibly) obsolete help files
    

    # check for dead links
    if(defined $helpFiles{$directory}) {
        print "Checking help files for dead links (language \"$language\")\n" if($debug);
        my $extractor = HTML::LinkExtor->new();
        foreach my $file (keys %{$helpFiles{$directory}})
        {
            if($file =~ /\.html$/) { 
                $file = "$file";
                $extractor->parse_file($file);
                for ($extractor->links() ) {
                    my ($tag, $type, $linkname) = @{$_};
                    $linkname = "\L$linkname";
                    # omit links beginning with '#'
                    next if($linkname =~ /^#/);
                    # omit external links beginning with 'http'
                    next if($linkname =~ /^http/);
                    # omit external links beginning with 'mailto'
                    next if($linkname =~ /^mailto/);
                    # discard the part of links that contain internal references ('#')
                    if($linkname =~ /(.*)#.*/) {
                        $linkname = $1;
                    } 
                    # build full link name (with full path)
                    $linkname = "\L$helpDirectory/$linkname";
                    $linkname =~ s/\\/\//g; # windows?
                    $possibleLinks{"$linkname"} = "$file";
                }
            }
        }
    
        foreach my $possibleLink (keys %possibleLinks) {
            if(not exists ${helpFiles{$helpDirectory}}{"$possibleLink"}) {
                print "  WARNING: file $possibleLink is missing (referenced in $possibleLinks{$possibleLink})\n" if($debug);
                $numberOfDeadLinks++;
            }
        }
    }

    print "\nSUMMARY (language \"$language\")\n";
    print "- $numberOfMissingDialogIdentifiers missing help files for dialog identifiers\n";
    print "- $numberOfMissingMenuIdentifiers missing help files for menu identifiers\n";
    print "- $numberOfDeadLinks dead links\n";
    print "\n(run CheckHelp.pl manually in debug mode for further details)\n\n";
}