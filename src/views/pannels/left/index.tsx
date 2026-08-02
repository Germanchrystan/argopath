import EntitiesPalette from './entities_palette';
import ScenePalette from './scene_palette';
import './styles.scss';

const LeftPannel = () => {
  return (
    <div className="left-pannel">
      <ScenePalette options={['scene 1']} />
      <EntitiesPalette />
    </div>
  )
}

export default LeftPannel;