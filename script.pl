#!/bin/bin/perl

sub forAll()
{
	my $FileName;

	open(Liste,"test/test.txt");
	while(!eof(Liste)) {
		chop($FileName=<Liste>);
		system(bash script.sh $Filename);
	}
	close(Liste);
}

forAll();

