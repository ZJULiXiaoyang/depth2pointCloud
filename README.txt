cd build
cmake ..
make 
./depth2cloud "rgb image" "depth image" "pcd file name"
for example:
./depth2cloud Img310.png Depth310.png pointcloud1.pcd
after that you can open a shell and input command "pcl_viewer pointcloud1.pcd" to show then pointcloud
