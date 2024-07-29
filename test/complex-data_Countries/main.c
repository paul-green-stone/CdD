#include "countries.h"

int main(int argc, char** argv) {
    
    extern char *optarg;
    extern int optind, opterr, optopt;
    
    const char* filename = "countries.bin";
    const char* optstr = ":";
    
    int opt = 0;
    
    char* name;
    char* capital;
    char* president;
    char* currency;
    
    double area;
    char* _area;
    
    size_t population;
    char* _population;
    
    int year;
    char* _year;
    
    Country* c;
    
    Dict_t dictionary;
    
    /* ================================================================ */
    /* ===================== Command Line Parsing ===================== */
    /* ================================================================ */
    
    while (1) {
        
        int index = 0;
        
        static struct option options[] = {
            {"name", required_argument, NULL, 0},
            {"capital", required_argument, NULL, 1},
            {"president", optional_argument, NULL, 2},
            {"currency", optional_argument, NULL, 3},
            {"area", optional_argument, NULL, 4},
            {"population", optional_argument, NULL, 5},
            {"year", optional_argument, NULL, 6},
        };
        
        if ((opt = getopt_long(argc, argv, optstr, options, &index)) == -1) {
            break ;
        }
        
        /* ================================================================ */
        
        switch (opt) {
            
            /* Name */
            case 0:
                name = optarg;
                
                break ;
            
            /* ======== */
                
            /* Capital */
            case 1:
                capital = optarg;
                
                break ;
                
            /* ======== */
                
            /* President */
            case 2:
                president = optarg ? optarg : "missing information";
                
                break ;
                
            /* ======== */
                
            /* Currency */
            case 3:
                currency = optarg ? optarg : "missing information";
                
                break ;
                
            /* ======== */
                
            /* Area */
            case 4:
                _area = optarg ? optarg : "missing information";
                
                break ;
                
            /* ======== */
            
            /* Population */
            case 5:
                _population = optarg ? optarg : "missing information";
                
                break ;
                
            /* ======== */   
                
            /* Year */
            case 6:
                _year = optarg ? optarg : "missing information";
                
                break ;
                
            /* ======== */   
            
            case '?':
                printf("Unknown option: -%c\n", optopt);
                
                break ;
                
            /* ======== */
                
            case ':':
                printf("Missing argument for -%c\n", optopt);
                
                break ;
        }
    }
    
    /* ================================================================ */
    
    area = strtod(_area, NULL);
    population = strtoul(_population, NULL, 10);
    year = atoi(_year);
    
    if ((c = Country_new(name, capital, president, currency, area, population, year)) == NULL) {
        printf("Unable to create a new entry - %s\n", strerror(errno));
        
        /* ======== */
        return EXIT_FAILURE;
    }
    
    if ((dictionary = Dict_new(199, (void (*)(void*)) Country_print, NULL, (void (*)(void*, FILE*)) Country_save, NULL)) == NULL) {
        printf("Unable to load a dictionary - %s\n", strerror(errno));
        
        /* ======== */
        return EXIT_FAILURE;
    }
    
    Dict_insert(name, c, dictionary);
    Dict_save(dictionary, filename);
    
    Country_destroy(&c);
    
    Dict_destroy(dictionary);
    
    /* ======== */
    
    return EXIT_SUCCESS;
}
