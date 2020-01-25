# centralized-blockchain
An implementation of Lamport's Distributed Mutual Exclusion Algorithm.

## Usage Instructions:

- Update the <b>config.txt</b> file with the ip address and port number of participating nodes. (Format is provided at the end of the config.txt file)
- Open <b>run.sh</b> and update the variable num_client with the number of clients you want to have in your system.
- Execute <b>run.sh</b>. It will start a new terminal for each of the participating nodes.
- Command for querying the balance for a node: <code>BAL</code>
- Command for transfering money to another client: <code> SEND <receiver_client_id> \<amount\> </code>
