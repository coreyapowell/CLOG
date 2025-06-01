import * as std from "qjs:std";
import * as os from "qjs:os";

var argv = scriptArgs;
var argc = argv.length;
function alert(s) { console.log(s); };

var infile, outfile, clogs;

/* unclog: takes an infile and writes to outfile.
    file is robbed of clogs! 
    clogs: array of strings to unclog
    rob example: ["CLOG(","FLOG("]
 */

function unclog(infile, outfile, clogs) {
    
    var lines = 0;
     while (true) {
        var found = 0;
        if (infile.eof()) return lines;
        var ln = infile.getline();
        if (!ln) {
            lines++;
            outfile.puts("\r\n");
            continue;
        };
        for  (var i in clogs) {
            var scan = ln.indexOf(clogs[i] + "(");
            if (scan != -1) {
                found = 1;
                scan = ln.indexOf(';')
                while (scan == -1) {
                    if (infile.eof()) return lines;
                    ln = infile.getline();
                    if (!ln) continue;
                    scan = ln.indexOf(';');
                };
                break;
            };
        };
        if (found) continue;
        lines++;
        outfile.puts(ln + "\n");
    };
};

function usage() {
    console.log('usage: unclog file.mess.c file.c "CLOG,FLOG,BLOG"');
    if (infile) infile.close();
    if (outfile) outfile.close();
    std.exit(1);
};

if (argc < 3) usage();
infile = std.open(argv[1], "r");
if (!infile) usage();
outfile = std.open(argv[2], "w");
if (argc >= 4) clogs = argv[3].split(",");
else clogs = ["CLOG","FLOG","BLOG"];
console.log("lines: " + unclog(infile, outfile, clogs) );

infile.close();
outfile.close();
