import { useEffect } from 'react'
import './App.scss'
import loadWasm from './helper/load-wasm';
import LeftPannel from './views/pannels/left';
import { useAppStore } from './store/app-store'
import ModalWrapper from './components/modal-wrapper';

function App() {
  const setWasmLoaded = useAppStore((state) => state.setWasmLoaded);
  const modal = useAppStore((state) => state.modal);

  useEffect(() => {
    const canvas = document.getElementById('canvas') as HTMLCanvasElement;
    loadWasm('argopath', canvas);
    setWasmLoaded(true)
  }, []);
  
  return (
    <>
    {
      modal && (
        <ModalWrapper modal={modal} />
      )
    }
      <LeftPannel />
      <section id="center">
        <canvas id="canvas" width="600" height="600" />
      </section>
    </>
  )
}

export default App
