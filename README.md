# irc42

**Un mini serveur IRC écrit de zéro en C++98.**  
**A small IRC server written from scratch in C++98.**

[🇫🇷 Lire en français](#francais) · [🇬🇧 Read in English](#english)

---

<a id="francais" name="francais"></a>
## 🇫🇷 Français

### Le projet en deux mots

IRC (*Internet Relay Chat*) est un protocole de discussion textuelle né en 1988. Il fait encore tourner de nombreuses communautés open source. Un serveur IRC est le programme central auquel tout le monde se connecte : il garde la liste des utilisateurs, des canaux (les « salons »), et distribue les messages.

**irc42 est un petit serveur IRC construit de zéro.** On le lance sur une machine, on y connecte quelques clients IRC, et on obtient un vrai salon de discussion : les gens s'inscrivent, rejoignent des canaux, discutent en public ou en privé, définissent un sujet, s'invitent, s'expulsent et modèrent le canal avec des modes.

L'analogie la plus simple : un petit Discord ou groupe WhatsApp auto-hébergé, mais implémenté au niveau du protocole réseau, sans framework de chat, sans base de données et sans service externe.

C'est le projet `ft_irc` de 42 Paris. L'objectif était d'apprendre le **C++** et la **programmation orientée objet** en construisant un vrai service réseau. C'est un **serveur unique** : il ne se connecte pas à d'autres serveurs IRC pour former un réseau fédéré.

### En un coup d'œil

| | |
|---|---|
| **Type** | Service réseau / serveur de discussion |
| **Langage** | C++98 |
| **Réseau** | TCP, multiplexage `epoll` sous Linux |
| **Dépendances** | Aucune (bibliothèque standard + appels système POSIX) |
| **Contexte** | Projet d'école `ft_irc`, 42 Paris |
| **Équipe** | 2 étudiants |

### Ce que le serveur sait faire

#### Discussion

- Accepter plusieurs clients en même temps et garder chaque connexion indépendante.
- Créer un canal automatiquement quand le premier utilisateur le rejoint, et le supprimer quand le dernier le quitte.
- Envoyer des messages publics dans un canal ou des messages privés à un utilisateur.
- Propager les changements de pseudo à tous les canaux concernés.
- Prévenir les autres membres quand quelqu'un se déconnecte ou quitte un canal.
- Gérer les commandes arrivant en morceaux (un message réseau n'arrive pas toujours d'un seul bloc).

#### Gestion des canaux

- Le premier utilisateur à rejoindre un canal en devient **opérateur**.
- `KICK` : expulser un membre du canal.
- `INVITE` : inviter quelqu'un dans un canal.
- `TOPIC` : consulter ou modifier le sujet du canal.
- Modes de canal disponibles :
  - `+i` : canal sur invitation uniquement.
  - `+t` : le sujet ne peut être changé que par un opérateur.
  - `+k` : canal protégé par un mot de passe.
  - `+o` : donner ou retirer le statut d'opérateur.
  - `+l` : limiter le nombre de membres du canal.

#### Inscription et informations

- `PASS`, `NICK`, `USER` : inscription avec mot de passe serveur, pseudo et nom réel.
- Messages de bienvenue et réponses numériques au format IRC.
- `WHOIS` : informations sur un utilisateur connecté.
- `WHOWAS` : historique des anciens pseudos, conservé en mémoire.
- `PING` / `PONG`, `version` (en minuscules dans cette implémentation), `QUIT`.
- `CAP` : poignée de main minimale pour les clients IRC modernes (aucune capacité supplémentaire annoncée).

#### Côté serveur

- Boucle d'événements `epoll` : un seul processus surveille le serveur, les clients et l'entrée standard.
- Sockets non bloquantes avec tampons d'entrée et de sortie.
- Déconnexions propres, y compris en cas de coupure brutale.
- Arrêt propre sur `SIGINT`, `SIGTERM` ou `SIGQUIT`.
- Console d'administration locale :
  - `monitor` / `mon` : nombre de clients et de canaux.
  - `dump client <pseudo>` : détails d'un client.
  - `dump channel <canal>` : détails d'un canal.
  - `dbg` / `debug` : activer ou désactiver les traces de debug.
  - `help` / `h` : afficher l'aide.
  - `quit` / `exit` : arrêter le serveur.

### Essayer le projet

Prérequis : un compilateur C++, `make`, et Linux (le serveur utilise `epoll`).

```bash
git clone https://github.com/AlphanumericString/irc42.git
cd irc42
make
./ircserv 6667 mypassword
```

Le serveur écoute alors sur le port `6667` avec le mot de passe `mypassword`.
On peut s'y connecter avec un client IRC classique (en indiquant `127.0.0.1`, port `6667`, mot de passe `mypassword`) ou directement avec `netcat` :

```text
nc 127.0.0.1 6667
PASS mypassword
NICK alice
USER alice 0 * :Alice
JOIN #general
PRIVMSG #general :Bonjour tout le monde !
```

Exemple de ce que reçoit le client après le `JOIN` :

```text
:alice!alice@localhost JOIN :#general
:42irc_server_apbg 331 alice #general :No topic set for channel #general.
:42irc_server_apbg 353 alice = #general :@alice
:42irc_server_apbg 366 alice #general :end of /NAMES list.
```

Le `@` devant `alice` signifie qu'elle est opératrice du canal. Quand un second utilisateur rejoint, le premier reçoit son arrivée ; quand Alice écrit, tout le canal reçoit :

```text
:bob!bob@localhost JOIN :#general
:alice!alice@localhost PRIVMSG #general :Bonjour tout le monde !
:alice!alice@localhost TOPIC #general :Bienvenue sur #general
```

### Quelques commandes utiles

| Commande | Rôle | Exemple |
|---|---|---|
| `PASS` | Donner le mot de passe du serveur | `PASS mypassword` |
| `NICK` | Choisir ou changer de pseudo | `NICK alice` |
| `USER` | Envoyer le nom d'utilisateur et le nom réel | `USER alice 0 * :Alice` |
| `JOIN` | Rejoindre ou créer un canal | `JOIN #general` |
| `PRIVMSG` | Envoyer un message public ou privé | `PRIVMSG #general :Salut !` |
| `PART` | Quitter un canal | `PART #general :À plus tard` |
| `TOPIC` | Lire ou changer le sujet d'un canal | `TOPIC #general :Bienvenue` |
| `MODE` | Lire ou modifier les modes d'un canal | `MODE #general +t` |
| `INVITE` | Inviter un utilisateur dans un canal | `INVITE bob #general` |
| `KICK` | Expulser un utilisateur d'un canal | `KICK #general bob :Trop de bruit` |
| `WHOIS` | Voir les informations d'un utilisateur | `WHOIS alice` |
| `WHOWAS` | Retrouver un ancien utilisateur | `WHOWAS alice` |
| `PING` | Vérifier que le serveur répond | `PING :hello` |
| `version` | Demander la version du serveur (en minuscules) | `version` |
| `QUIT` | Se déconnecter | `QUIT :À bientôt` |

### Sous le capot : ce que ce projet démontre

- **Programmation orientée objet en C++98** : classes `Server`, `ServerState`, `Client`, `Channel`, hiérarchie de commandes `ICmd`, objets de réponse `IRPL` et d'erreur `IError`, avec responsabilités séparées.
- **Réseau événementiel** : un seul thread, plusieurs clients, sockets non bloquantes, tampons d'entrée/sortie et gestion des messages partiels.
- **Implémentation de protocole** : inscription, réponses numériques, erreurs, modes de canal, privilèges opérateur, `WHOIS`, `WHOWAS`.
- **Robustesse** : gestion des déconnexions, des signaux, des canaux vides et des erreurs de protocole sans arrêter le serveur.
- **Ingénierie** : `Makefile` avec `-Wall -Wextra -Werror`, dépendances automatiques, build de développement avec AddressSanitizer et UndefinedBehaviorSanitizer, build de production avec optimisation et LTO.
- **Travail en équipe** : projet mené à deux, avec un historique Git suivi.

### Ce qui manque (limites assumées)

Ce projet est un **projet d'apprentissage**, pas un serveur IRC de production.

- **Pas de réseau fédéré** : un seul serveur, pas de connexion serveur-à-serveur.
- **Pas de TLS/SSL** : les échanges circulent en clair.
- **Pas d'IPv6**, pas de résolution DNS/ident.
- **Pas d'IRCv3** ni de négociation de capacités avancée.
- **Commandes absentes ou partielles** : `NOTICE`, `WHO`, `NAMES`, `LIST`, `AWAY`, `MOTD`, `ADMIN`, `OPER`, `USERHOST`, `ISON`, etc.
- **Modes utilisateur non pris en charge** : seuls les modes de canal sont gérés.
- **Analyse des commandes sensible à la casse** : `version` doit être envoyé en minuscules ; les autres commandes sont écrites en majuscules.
- **Modes de canal limités** : `i`, `t`, `k`, `o`, `l` uniquement ; pas de bannissement, de « voice », de canal modéré, secret ou privé.
- **Pas de traitement de plusieurs canaux à la fois** : `JOIN` et `PART` traitent un canal à la fois, sans jokers ni masques.
- **Pas d'historique de messages** ni de persistance : utilisateurs, canaux et `WHOWAS` disparaissent au redémarrage.
- **Pas de timeout automatique** : pas de déconnexion sur inactivité, pas de limite de connexions, pas de protection anti-flood.
- **Pas de hachage du mot de passe** : le mot de passe serveur est comparé en clair.
- **WHOIS/WHOWAS minimalistes** : certaines réponses restent approximatives ; le code contient encore des commentaires `FIX` à ce sujet.
- **Pas de suite de tests automatisés ni de CI.**
- **Pas de fichier de configuration**, pas de mode démon, pas de journaux persistants.
- **Pas d'audit de sécurité** : à utiliser sur un réseau de confiance, idéalement en local.

### Valeurs par défaut et configuration

| Élément | Valeur |
|---|---|
| Exécutable | `ircserv` |
| Arguments requis | `./ircserv <port> <mot_de_passe>` |
| Plage de ports acceptée | 1024 à 49151 |
| Port par défaut défini dans le code | `8080` (constante `SERVER_PORT_DFLT`) |
| Mot de passe par défaut défini dans le code | `password` (constante `SERVER_PWD_DFLT`) |
| Nom du serveur | `42irc_server_apbg` |
| Hôte annoncé | `localhost` |
| Pseudo maximum | 9 caractères |
| Nom de canal maximum | 200 caractères |
| Taille du tampon d'entrée/sortie | 8192 octets |
| Backlog d'écoute | 10 connexions |
| Lot d'événements `epoll` | 20 événements, timeout de 1 seconde |
| Standard de compilation | C++98, `-Wall -Wextra -Werror` |
| Build de développement | AddressSanitizer + UndefinedBehaviorSanitizer via `make DEPLOYMENT=dev re` |
| Build de production (par défaut) | `-O2 -flto` |
| Version | issue de `git describe --tags --dirty`, sinon `0.0.0` |

À noter : bien que les constantes `8080` et `password` existent, la fonction de lecture des arguments exige actuellement un port et un mot de passe explicites. Le mot de passe doit être composé uniquement de caractères alphanumériques.

[⬆ Retour en haut](#irc42) · [🇬🇧 English version](#english)

---

<a id="english" name="english"></a>
## 🇬🇧 English

### What is this project, in plain words?

IRC (*Internet Relay Chat*) is a text chat protocol created in 1988. It still powers many open-source communities. An IRC server is the central program everyone connects to: it keeps track of users and channels (chat rooms), and delivers messages.

**irc42 is a small IRC server built from scratch.** Start it on a machine, connect a few IRC clients, and you get a working chat room: people can register, join channels, talk in public or private, set a topic, invite or kick people, and moderate the channel with modes.

The simplest analogy: a self-hosted Discord server or WhatsApp group, but implemented at the network protocol level, with no chat framework, no database and no external service.

This is the `ft_irc` project from 42 Paris. The goal was to learn **C++** and **object-oriented programming** by building a real network service. It is a **single server**: it does not link to other IRC servers to form a federated network.

### At a glance

| | |
|---|---|
| **Type** | Network service / chat server |
| **Language** | C++98 |
| **Networking** | TCP, `epoll` multiplexing on Linux |
| **Dependencies** | None (standard library + POSIX system calls) |
| **Context** | `ft_irc` school project, 42 Paris |
| **Team** | 2 students |

### What the server can do

#### Chat

- Accept several clients at the same time and keep every connection independent.
- Create a channel automatically when the first user joins, and delete it when the last user leaves.
- Send public messages to a channel or private messages to a user.
- Propagate nickname changes to every channel the user is in.
- Notify other members when someone disconnects or leaves a channel.
- Handle commands that arrive in pieces (a network message does not always arrive in one block).

#### Channel management

- The first user to join a channel becomes a **channel operator**.
- `KICK`: remove a member from the channel.
- `INVITE`: invite someone to an invite-only channel.
- `TOPIC`: view or change the channel topic.
- Available channel modes:
  - `+i`: invite-only channel.
  - `+t`: only operators can change the topic.
  - `+k`: channel protected by a password.
  - `+o`: give or remove channel operator status.
  - `+l`: limit the number of channel members.

#### Registration and information

- `PASS`, `NICK`, `USER`: register with a server password, nickname and real name.
- IRC-style welcome messages and numeric replies.
- `WHOIS`: information about a connected user.
- `WHOWAS`: history of previous nicknames, kept in memory.
- `PING` / `PONG`, `version` (lowercase in this implementation), `QUIT`.
- `CAP`: minimal handshake for modern IRC clients (no extra capabilities advertised).

#### Server side

- `epoll` event loop: one process watches the server socket, clients and standard input.
- Non-blocking sockets with input and output buffers.
- Clean disconnects, including abrupt connection loss.
- Graceful shutdown on `SIGINT`, `SIGTERM` or `SIGQUIT`.
- Local administration console:
  - `monitor` / `mon`: number of clients and channels.
  - `dump client <nick>`: details about a client.
  - `dump channel <channel>`: details about a channel.
  - `dbg` / `debug`: enable or disable debug traces.
  - `help` / `h`: show help.
  - `quit` / `exit`: stop the server.

### Try it

Requirements: a C++ compiler, `make`, and Linux (the server uses `epoll`).

```bash
git clone https://github.com/AlphanumericString/irc42.git
cd irc42
make
./ircserv 6667 mypassword
```

The server now listens on port `6667` with the password `mypassword`.
You can connect with a regular IRC client (`127.0.0.1`, port `6667`, password `mypassword`) or directly with `netcat`:

```text
nc 127.0.0.1 6667
PASS mypassword
NICK alice
USER alice 0 * :Alice
JOIN #general
PRIVMSG #general :Hello everyone!
```

Example of what the client receives after `JOIN`:

```text
:alice!alice@localhost JOIN :#general
:42irc_server_apbg 331 alice #general :No topic set for channel #general.
:42irc_server_apbg 353 alice = #general :@alice
:42irc_server_apbg 366 alice #general :end of /NAMES list.
```

The `@` before `alice` means she is the channel operator. When a second user joins, the first one is notified; when Alice writes, the whole channel receives it:

```text
:bob!bob@localhost JOIN :#general
:alice!alice@localhost PRIVMSG #general :Hello everyone!
:alice!alice@localhost TOPIC #general :Welcome to #general
```

### A few useful commands

| Command | Purpose | Example |
|---|---|---|
| `PASS` | Send the server password | `PASS mypassword` |
| `NICK` | Choose or change a nickname | `NICK alice` |
| `USER` | Send the username and real name | `USER alice 0 * :Alice` |
| `JOIN` | Join or create a channel | `JOIN #general` |
| `PRIVMSG` | Send a public or private message | `PRIVMSG #general :Hi!` |
| `PART` | Leave a channel | `PART #general :See you` |
| `TOPIC` | Read or change a channel topic | `TOPIC #general :Welcome` |
| `MODE` | Read or change channel modes | `MODE #general +t` |
| `INVITE` | Invite a user to a channel | `INVITE bob #general` |
| `KICK` | Remove a user from a channel | `KICK #general bob :Too noisy` |
| `WHOIS` | Show information about a user | `WHOIS alice` |
| `WHOWAS` | Look up a previous user | `WHOWAS alice` |
| `PING` | Check that the server answers | `PING :hello` |
| `version` | Ask for the server version (lowercase) | `version` |
| `QUIT` | Disconnect | `QUIT :Bye` |

### Under the hood: what this project demonstrates

- **Object-oriented C++98**: `Server`, `ServerState`, `Client` and `Channel` classes, an `ICmd` command hierarchy, `IRPL` reply objects and `IError` error objects, with separated responsibilities.
- **Event-driven networking**: one thread, many clients, non-blocking sockets, input/output buffers, and partial-message handling.
- **Protocol implementation**: registration, numeric replies, errors, channel modes, operator privileges, `WHOIS`, `WHOWAS`.
- **Robustness**: handling disconnects, signals, empty channels and protocol errors without crashing the server.
- **Engineering**: a `Makefile` with `-Wall -Wextra -Werror`, automatic dependencies, a development build with AddressSanitizer and UndefinedBehaviorSanitizer, and an optimized LTO production build.
- **Teamwork**: a two-person project with a tracked Git history.

### What is missing (known limitations)

This is a **learning project**, not a production IRC server.

- **No federated network**: one server only, no server-to-server linking.
- **No TLS/SSL**: traffic is sent in clear text.
- **No IPv6**, no DNS/ident lookup.
- **No IRCv3** and no advanced capability negotiation.
- **Missing or partial commands**: `NOTICE`, `WHO`, `NAMES`, `LIST`, `AWAY`, `MOTD`, `ADMIN`, `OPER`, `USERHOST`, `ISON`, etc.
- **No user modes**: only channel modes are implemented.
- **Case-sensitive command parsing**: `version` must be sent in lowercase; the other commands are uppercase.
- **Limited channel modes**: only `i`, `t`, `k`, `o`, `l`; no bans, voice, moderated, secret or private channels.
- **No multi-channel commands**: `JOIN` and `PART` handle one channel at a time, with no wildcards or masks.
- **No message history or persistence**: users, channels and `WHOWAS` data disappear after a restart.
- **No automatic timeout**: no idle disconnect, connection limit or flood protection.
- **No password hashing**: the server password is compared in plain text.
- **Minimal WHOIS/WHOWAS**: some replies remain approximate; the source still contains `FIX` comments about this.
- **No automated test suite or CI.**
- **No configuration file**, no daemon mode, no persistent logs.
- **No security audit**: use it on a trusted network, ideally locally.

### Defaults and configuration

| Item | Value |
|---|---|
| Executable | `ircserv` |
| Required arguments | `./ircserv <port> <password>` |
| Accepted port range | 1024 to 49151 |
| Default port defined in code | `8080` (`SERVER_PORT_DFLT` constant) |
| Default password defined in code | `password` (`SERVER_PWD_DFLT` constant) |
| Server name | `42irc_server_apbg` |
| Advertised host | `localhost` |
| Maximum nickname length | 9 characters |
| Maximum channel name length | 200 characters |
| Input/output buffer size | 8192 bytes |
| Listen backlog | 10 connections |
| `epoll` event batch | 20 events, 1 second timeout |
| Compilation standard | C++98, `-Wall -Wextra -Werror` |
| Development build | AddressSanitizer + UndefinedBehaviorSanitizer via `make DEPLOYMENT=dev re` |
| Production build (default) | `-O2 -flto` |
| Version | from `git describe --tags --dirty`, otherwise `0.0.0` |

Note: although the `8080` and `password` constants exist, the argument parser currently requires an explicit port and password. The password must contain only alphanumeric characters.

[⬆ Back to top](#irc42) · [🇫🇷 Version française](#francais)
