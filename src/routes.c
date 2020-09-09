/*
 * SeaTraffic
 *
 * (c) Jonathan Harris 2012
 *
 */

#include "seatraffic.h"

/* Globals */
static route_list_t *routes[180][360];	/* array of link lists of routes by tile */

/* prototypes */
static int addroutetotile(route_t *route);


int readroutes(char *mypath, char *err)
{
    char buffer[PATH_MAX], *c;
    FILE *h;
    int lineno=0;
    route_t *currentroute=NULL;

    strcpy(buffer, mypath);
    strcat(buffer, "routes.txt");
    if (!(h=fopen(buffer, "r")))
    {
        strcpy(err, "Can't open routes.txt");
        return 0;
    }
    if (!(c=fgets(buffer, PATH_MAX, h)))
    {
        fclose(h);
        strcpy(err, "Can't read routes.txt");
        return 0;
    }
    if (!strncmp(c, "\xef\xbb\xbf", 3)) { c+=3; }	/* skip Unicode BOM */
    while (c)
    {
        lineno++;
        while (isspace(*c)) { c++; }	/* ltrim */
        if (*c == '#')			/* Skip comment lines */
        {
        }
        else if (!*c)			/* Blank line = end of record */
        {
            if (currentroute)
            {
                if (currentroute->pathlen)
                {
                    if (!addroutetotile(currentroute))
                    {
                        strcpy(err, "Out of memory");
                        return 0;
                    }
                }
                else
                {
                    sprintf(err, "Empty route at routes.txt line %d", lineno);
                    return 0;
                }
                currentroute=NULL;
            }
        }
        else if (currentroute)		/* New point on path of existing route */
        {
            if (!(currentroute->path=realloc(currentroute->path, (currentroute->pathlen+1)*sizeof(loc_t))))
            {
                strcpy(err, "Out of memory");
                return 0;
            }
            if (sscanf(c, "%f %f", &(currentroute->path[currentroute->pathlen].lat), &(currentroute->path[currentroute->pathlen].lon)) != 2)
            {
                sprintf(err, "Invalid location at routes.txt line %d", lineno);
                return 0;
            }
            currentroute->pathlen++;
        }
        else				/* New route */
        {
            int i;
            char *name=c;
            while ((*name) && !isspace(*name)) { name++; }	/* split line into shiptype and name */
            while ((*name) && isspace(*name)) { *(name++)=0; }	/* split line into shiptype and name */
            if (!(currentroute=calloc(1, sizeof(route_t))))
            {
                strcpy(err, "Out of memory");
                return 0;
            }
            for (i=0; i<ship_kind_count; i++)
            {
                if (!strcmp(c, ships[i].token))
                {
                    currentroute->ship_kind=i;
                    break;
                }
            }
            if (i==ship_kind_count)
            {
                sprintf(err, "Unrecognised ship type \"%s\" at routes.txt line %d", c, lineno);
                return 0;
            }
            // nst0022 2.1 activated begin
            c=name+strlen(name)-1;				/* name is utf-8 encoded, which X-Plane can render */
            while ((c>=name) && isspace(*c)) { *(c--)=0; };	/* rtrim */
            currentroute->name=strdup(name);
            // nst0022 2.1 activated end
        }
        c=fgets(buffer, PATH_MAX, h);
    }

    if (currentroute)			/* last one */
    {
        if (currentroute->pathlen)
        {
            if (!addroutetotile(currentroute))
            {
                strcpy(err, "Out of memory");
                return 0;
            }
        }
        else
        {
            sprintf(err, "Empty route at routes.txt line %d", lineno);
            return 0;
        }
    }

    fclose(h);

    return 1;
}


/* Add a route to the tile list */
static int addroutetotile(route_t *route)
{
    int i;
    for (i=0; i<route->pathlen; i++)
    {
        route_list_t **route_list;
        int south, west;
        south=(int)floor(route->path[i].lat);
        west=(int)floor(route->path[i].lon);
        route_list=&routes[south+90][west+180];

        if (!*route_list || (*route_list)->route!=route)	/* We add from front so only need to check first route */
        {
            if (!route_list_add(route_list, route)) { return 0; }
        }
    }
    return 1;
}


route_list_t *getroutesbytile(int south, int west)
{
    return routes[south+90][west+180];
}


/**********************************************************************
 Linked list manipulation
 **********************************************************************/

/* Allocates and adds to front of list */
route_list_t *route_list_add(route_list_t **route_list, route_t *route)
{
    route_list_t *newroute;
    if (!(newroute=malloc(sizeof(route_list_t)))) { return 0; }
    newroute->route=route;
    newroute->next=*route_list;
    *route_list=newroute;
    return *route_list;
}


route_list_t *route_list_get_byroute(route_list_t *route_list, route_t *route)
{
    while (route_list!=NULL)
    {
        if (route_list->route==route) { return route_list; }
        route_list=route_list->next;
    }
    return NULL;
}


/* Return nth item in list. Assumes that there are n items in list */
route_t *route_list_pop(route_list_t **route_list, int n)
{
    route_t *route;
    route_list_t *this, **lastptr=route_list;
    while (n--)
    {
        lastptr=&((*lastptr)->next);
        assert(*lastptr!=NULL);
    }
    this=*lastptr;
    route=this->route;
    *lastptr=this->next;
    if (this) // nst0022 2.1
    {
      free(this);
    }
    return route;
}


int route_list_length(route_list_t *route_list)
{
    int i=0;
    while (route_list!=NULL)
    {
        i++;
        route_list=route_list->next;
    }
    return i;
}


/* Free entire list */
void route_list_free(route_list_t **route_list)
{
    route_list_t *next;
    while (*route_list)
    {
        next=(*route_list)->next;
        if (* route_list) // nst0022 2.1
        {
          free(* route_list);
        }
        *route_list=next;
    }
}


/* Allocates and adds to front of list */
active_route_t *active_route_add(active_route_t **active_routes)
{
    active_route_t *newroute;
    if (!(newroute=malloc(sizeof(active_route_t)))) { return NULL; }
    newroute->next=*active_routes;
    *active_routes=newroute;
    return *active_routes;
}


active_route_t *active_route_get(active_route_t *active_routes, int n)
{
    while (n--)
    {
        active_routes=active_routes->next;
        // assert(active_routes!=NULL);	/* Allow function to return NULL for item just past length */
    }
    return active_routes;
}


active_route_t *active_route_get_byroute(active_route_t *active_routes, route_t *route)
{
    while (active_routes!=NULL)
    {
        if (active_routes->route==route) { return active_routes; }
        active_routes=active_routes->next;
    }
    return NULL;
}


void active_route_pop(active_route_t **active_routes, int n)
{
    active_route_t *this, **lastptr=active_routes;
    while (n--)
    {
        lastptr=&((*lastptr)->next);
        assert(*lastptr!=NULL);
    }
    this=*lastptr;
    *lastptr=this->next;
    if (this) // nst0022 2.1
    {
      free(this);
    }
}


int active_route_length(active_route_t *active_routes)
{
    int i=0;
    while (active_routes!=NULL)
    {
        i++;
        active_routes=active_routes->next;
    }
    return i;
}

// nst0022 2.3
///* Callback for active_route_sort */
//static int sortactive(const void *a, const void *b)
//{
//    const active_route_t *const *ra = a, *const *rb = b;
//    return strcmp((*ra)->object_name, (*rb)->object_name);
//}
//
//
///* Sort active routes by object name to minimise texture swaps when drawing.
// * Rather than actually shuffling the routes around in memory we just sort an array of pointers and then go back
// * and fix up the linked list. */
//void active_route_sort(active_route_t **active_routes, int active_n)
//{
//    int i;
//    active_route_t *table[ACTIVE_MAX], *active_route;
//
//    if (active_n <= 2) return;		/* Nothing useful to do */
//
//    for (i = 0, active_route = *active_routes; active_route; active_route = active_route->next)
//        table[i++] = active_route;
//    qsort(table, active_n, sizeof(active_route), sortactive);
//    *active_routes = table[0];  // nst0022 this does not look good, table is defined on the stack, but passed to the caller
//    for (i = 0; i < active_n; i++)
//        table[i]->next = i < active_n-1 ? table[i+1] : NULL;
//}
