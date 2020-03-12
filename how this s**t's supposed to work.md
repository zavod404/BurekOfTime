Ko prižgemo arduino mora ta preveriti, če je laser na obeh LDRjih, na ekranu se lahko naredi neka grafika za vsak laser posebej,
ki to ponazarja (tarča, prazna, če laser ne sveti v LDR in obratno). Šele ko je laser na LDRju nekaj sekund se program nadaljuje in zasveti
rdeča ledica, na zaslon se izpiše "ready". Potem program čaka na voznika. Ko ta prekine prvi laser se prižge še rumena ledica, na zaslon se izpiše 
"wait for it...". Ves ta čas do štarta se preverja, da voznik ne gre stran od prvega laserja in da ne prečka drugega. Če gre stran od prvega
laserja se mora postaviti še enkrat, če pa prekine drugi laser (prehitro spelje), pa arduino ne bo začel šteti časa.
Po random času po prekinitvi prvega laserja (med 3 in 5s) se ugasneta rdeča in rumena ledica, prižge se zelena in vklopi se buzzer (2s),
začne se merit cajt, na zaslon se izpiše "go" in po dveh sekundah začne pisati pretekli čas (na desetinko natančno). Potem se voznik pelje
okoli proge. Ko prečka drugi laser se neha merit cajt in se izpiše na zaslonu na 3 decimalke. Čas je prikazan v spodnji vrstici zaslona 10s, 
potem pa se namesto njega izpiše najboljši cajt (ostane če je zadnji najboljši), ki je vedno prikazan v spodnji vrstici. Lahko se doda še
kakšen napis, da se poudari, da je zadnji čas boljši/slabši od najboljšega. Ko voznik prečka štart gre arduino v pripravljenost za naslednjega
voznika.

Pozor: potrebno je paziti, da se laser večkrat prekine in sproži ko voznik štarta in prečka cilj.
