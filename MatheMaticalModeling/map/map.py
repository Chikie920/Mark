from pyecharts import options as opts
from pyecharts.charts import Map
from pyecharts.render import make_snapshot
from snapshot_selenium import snapshot

map = (
    Map(opts.InitOpts(width='600px', height='600px', page_title='地图示例'))
    .add('地图标题', [list(i) for i in zip(['湖北', '广东'],[100, 150])], 'china')
    .render('test.html')
)

map2 = (
    Map(opts.InitOpts(width='600px', height='600px', page_title='地图示例'))
    .add('地图标题', [list(i) for i in zip(['湖北', '广东'],[100, 150])], 'china')
)

make_snapshot(snapshot, map2.render(), 'image.png')