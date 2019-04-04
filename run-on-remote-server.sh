for host in $(cat hosts.txt);
do
scp ./supervisord.conf root@"$host":/etc/supervisord.conf
ssh -o StrictHostKeyChecking=no  root@"$host" /etc/init.d/supervisord restart
nc -zv $host 9998
echo $host
done