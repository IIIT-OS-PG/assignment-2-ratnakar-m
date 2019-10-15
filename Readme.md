## Assignment 2  (OS PG)
### Topic: Group based Peer-to-Peer file sharing system
### Submitted By: Ratnakar Rao Mallayagari (201550807)


### Overview of Group based Peer-to-Peer file sharing system
- Multiple Trackers behind a load balancer (for fault tolerance and load balancing)
- Data abstraction layer (containing user management data and files metadata)
- Peers: interface for users to share data with in their groups
![](artifacts/group_file_sharing.jpg)

### Peer-to-Peer communication steps
- User login to a peer and queries tracker for files available and gets their metadata containing the seeders list
- Requests the seeders to send the piece information
- Apply piece selection algorithm to optimize the data transfer between peers
- Actual file data transfer in pieces
- Notify tracker to add as seeder once the piece is available.
![](artifacts/dowload_steps.jpg)

### Technical Overview
#### Directory and File structure
![](artifacts/code_structure_overview.jpg)
#### Technical concepts
- Server Client Communication
- Multi threading
- Hashing for integrity check
- Piece Selection Algorithm
- File Access

#### Dependencies
- pthread (multithreading)
- crypto (hashing)
- jsoncpp (data exchanage format between systems)

#### Functional Aspects:
##### User Interface Commands Representations
- Create User
- Login
- Create Group
- Join Group
- Leave Group
- List Pending Requests
- Accept Request
- List Groups
- List Files
- Upload File
- Download File
- Show Downloads
- Stop Shares
- Logout

![](artifacts/user_commands_rep.jpg)

#### Integration aspects:
##### Internal APIs as part of Download scenario
- get_file_info -> API to get file information from tracker
- get_piece_info -> API to get piece information from the seeder
- download_piece -> API to download a particular piece
- update_seeders_list -> Update seeders list after piece is downloaded
- update_status -> update download status
